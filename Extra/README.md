# AVL Tree Visualization System (Pro)
### 数据结构课程大作业 - 动态平衡二叉树可视化系统

![Python](https://img.shields.io/badge/Python-3.8+-blue.svg)
![Flask](https://img.shields.io/badge/Framework-Flask-green.svg)
![Vis.js](https://img.shields.io/badge/Frontend-Vis.js-orange.svg)
![Status](https://img.shields.io/badge/Status-Completed-success.svg)

## 📖 项目简介 (Introduction)

本项目是一个**全栈式 AVL 树动态可视化教学演示系统**。

不同于传统的控制台程序，本系统采用了现代化的 **B/S 架构 (Browser/Server)**。后端使用 **Python (Flask)** 实现严谨的 AVL 树算法逻辑，前端使用 **Vis.js** 物理引擎进行动态渲染。

**核心亮点：**
本系统不仅仅展示最终结果，更致力于**“思维过程的可视化”**。当插入节点导致树失衡时，系统会自动生成操作步骤序列，以慢动作动画的形式演示：
1.  **失衡检测**：高亮显示失衡节点。
2.  **旋转判定**：识别 LL/RR/LR/RL 四种旋转类型。
3.  **动态调整**：平滑展示节点旋转、父子关系变更的物理移动过程。

---

## ✨ 功能特性 (Features)

* **⚡ 核心算法引擎**：
    * 完整实现了标准 AVL 树的插入、删除（含再平衡）逻辑。
    * 支持高度计算、平衡因子实时监测。
* **🎥 异步动画队列 (Step-by-Step Animation)**：
    * 引入“快照 (Snapshot)”机制，后端记录每一次树结构的变化。
    * 前端实现异步队列播放器，将瞬间完成的算法步骤分解为连续的动画流。
* **🧠 智能日志系统 (Smart Logging)**：
    * 右侧悬浮面板实时输出系统决策日志。
    * 关键操作（如“发现失衡”、“执行左旋”）会自动高亮，辅助教学讲解。
* **🎨 交互式可视化 (Interactive Canvas)**：
    * 基于 Vis.js 物理引擎，节点插入时具有自然的弹性和阻尼效果。
    * 支持鼠标滚轮缩放、拖拽画布，可轻松查看大型树结构。
    * **颜色编码**：普通节点为蓝色，旋转轴心节点在操作时自动变为**橙色**。

---

## 🛠️ 技术栈 (Tech Stack)

| 模块 | 技术选型 | 说明 |
| :--- | :--- | :--- |
| **Backend** | Python 3 + Flask | 负责 AVL 逻辑运算、步骤快照生成、RESTful API 接口。 |
| **Frontend** | HTML5 + CSS3 | 现代化 Flex 布局，响应式设计。 |
| **Visualization** | Vis.js (Network) | 负责拓扑图渲染、物理力导向动画。 |
| **Logic** | JavaScript (ES6+) | async/await 异步控制、动画队列管理。 |

---

## 🚀 快速开始 (Quick Start)

### 1. 环境准备
确保你的电脑已安装 Python 3.x。

### 2. 安装依赖
在项目根目录下运行以下命令安装 Flask：

```bash
pip install flask