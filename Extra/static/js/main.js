// 全局变量
let network = null;
let networkData = {
    nodes: new vis.DataSet([]),
    edges: new vis.DataSet([])
};
let isAnimating = false; // 锁：防止动画播放时重复提交

// --- 初始化 Vis.js ---
function initVis() {
    const container = document.getElementById('mynetwork');
    
    const options = {
        layout: {
            hierarchical: {
                direction: 'UD',        // Up-Down: 从上到下排列
                sortMethod: 'directed', // 确保树的层次结构正确
                levelSeparation: 80,    // 层级高度
                nodeSpacing: 100        // 节点间距
            }
        },
        nodes: {
            shape: 'circle',
            font: { color: 'white', size: 18 },
            borderWidth: 2,
            shadow: true,
            color: {
                background: '#3498db',
                border: '#2980b9'
            }
        },
        edges: {
            width: 2,
            color: '#95a5a6',
            smooth: {
                type: 'cubicBezier',    // 贝塞尔曲线
                forceDirection: 'vertical',
                roundness: 0.4
            }
        },
        physics: {
            enabled: true,
            hierarchicalRepulsion: {
                nodeDistance: 120,
                springLength: 100,
                damping: 0.5
            },
            stabilization: {
                iterations: 200, 
                fit: true 
            }
        },
        interaction: {
            dragNodes: false, // 禁止手动拖拽，保持树形结构整洁
            zoomView: true,
            dragView: true
        }
    };

    network = new vis.Network(container, networkData, options);
}

// --- 辅助工具函数 ---

// 1. 睡眠函数 (实现暂停效果)
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// 2. 日志添加函数
function addLog(message, isImportant = false) {
    const logDiv = document.getElementById('log-content');
    const entry = document.createElement('div');
    
    // 设置样式类
    entry.className = isImportant ? 'log-entry log-highlight' : 'log-entry';
    
    // 添加时间戳
    const time = new Date().toLocaleTimeString().split(' ')[0];
    entry.innerHTML = `<span style="color:#999;font-size:0.75rem;">[${time}]</span> ${message}`;
    
    logDiv.appendChild(entry);
    logDiv.scrollTop = logDiv.scrollHeight; // 自动滚动到底部
}

// --- 核心交互逻辑 ---

async function insertNode() {
    // 如果正在播放动画，禁止新操作
    if (isAnimating) {
        alert("请等待当前动画播放完毕");
        return;
    }

    const inputField = document.getElementById('insertValue');
    const value = inputField.value;

    if (!value) {
        alert("请输入数字！");
        return;
    }

    try {
        // 1. 发送请求给后端
        const response = await fetch('/api/insert', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ value: value })
        });

        const result = await response.json();

        if (result.status === 'success') {
            inputField.value = ''; // 清空输入框
            // 2. 启动动画队列播放
            await playAnimationSteps(result.steps);
        } else {
            alert("错误: " + result.message);
        }

    } catch (error) {
        console.error("API Error:", error);
        addLog("错误: 无法连接服务器", true);
    }
}

async function deleteNode() {
    if (isAnimating) {
        alert("请等待当前动画播放完毕");
        return;
    }

    const inputField = document.getElementById('deleteValue');
    const value = inputField.value;

    if (!value) {
        alert("请输入要删除的数字");
        return;
    }

    try {
        const response = await fetch('/api/delete', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ value: value })
        });

        const result = await response.json();

        if (result.status === 'success') {
            inputField.value = ''; 
            await playAnimationSteps(result.steps);
        } else {
            alert("错误: " + result.message);
        }

    } catch (error) {
        console.error("API Error:", error);
        addLog("错误: 无法连接服务器", true);
    }
}

async function resetTree() {
    if (isAnimating) return;
    if (!confirm("确定要清空整棵树吗？")) return;

    try {
        const response = await fetch('/api/reset', { method: 'POST' });
        const result = await response.json();
        
        // 重置通常不需要分步动画，直接刷新
        updateGraph(result.data);
        document.getElementById('log-content').innerHTML = '<div style="color:#aaa; font-style:italic;">系统已重置...</div>';
        addLog("系统已重置。");
        
    } catch (error) {
        console.error(error);
    }
}

// --- 动画引擎 ---

async function playAnimationSteps(steps) {
    isAnimating = true;
    
    // 禁用所有操作按钮
    const buttons = document.querySelectorAll('button');
    buttons.forEach(btn => btn.disabled = true);

    // 遍历每一个步骤
    for (let i = 0; i < steps.length; i++) {
        const step = steps[i];
        
        // 1. 更新图形
        updateGraph(step.tree_data);
        
        // 2. 更新日志
        // 如果日志包含“失衡”或“旋转”，则高亮显示
        const isImportant = step.log.includes("失衡") || step.log.includes("旋转") || step.log.includes("操作完成");
        addLog(step.log, isImportant);
        
        // 3. 关键暂停：留出时间给 Vis.js 物理引擎移动节点，也给用户看清变化
        // 如果是最后一步，时间短一点；如果是中间步骤，时间长一点
        const delay = (i === steps.length - 1) ? 500 : 1200;
        await sleep(delay);
    }

    // 恢复状态
    isAnimating = false;
    buttons.forEach(btn => btn.disabled = false);
}

// 更新视图数据
function updateGraph(data) {
    // 使用 Vis.js DataSet 的 update 机制
    // 只有变化的节点会移动，不变的节点保持静止
    networkData.nodes.clear();
    networkData.edges.clear();
    networkData.nodes.add(data.nodes);
    networkData.edges.add(data.edges);
    
    // 如果节点数量少，自动适配视角
    if (data.nodes.length < 15) {
        network.fit({ 
            animation: { 
                duration: 500, 
                easingFunction: 'easeInOutQuad' 
            } 
        });
    }
}

// 页面加载完成后初始化
window.onload = function() {
    initVis();
};