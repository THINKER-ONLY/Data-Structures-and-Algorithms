import json

class TreeNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1
        self.id = str(key)

class AVLTree:
    def __init__(self):
        self.root = None
        # 核心：用于存储动画步骤的列表
        self.steps = [] 

    # --- 辅助方法 ---
    def get_height(self, node):
        if not node: return 0
        return node.height

    def get_balance(self, node):
        if not node: return 0
        return self.get_height(node.left) - self.get_height(node.right)

    # --- 快照功能：核心 ---
    def snapshot(self, message, highlight_nodes=None):
        """
        记录当前树的状态。
        message: 这一步的操作说明（用于前端日志）
        highlight_nodes: 需要高亮的节点ID列表 (可选)
        """
        tree_json = self.to_json(highlight_nodes)
        self.steps.append({
            "tree_data": tree_json,
            "log": message
        })

    def to_json(self, highlight_nodes=None):
        nodes = []
        edges = []
        if highlight_nodes is None: highlight_nodes = []
        
        if not self.root:
            return {"nodes": [], "edges": []}
            
        def traverse(node):
            # 默认颜色
            color = {'background': '#3498db', 'border': '#2980b9'}
            
            # 如果是高亮节点（比如旋转轴心），变成橙色
            if node.id in highlight_nodes:
                color = {'background': '#e67e22', 'border': '#d35400'}
                
            nodes.append({
                "id": node.id, 
                "label": str(node.key),
                "color": color
            })
            
            if node.left:
                edges.append({"from": node.id, "to": node.left.id})
                traverse(node.left)
            if node.right:
                edges.append({"from": node.id, "to": node.right.id})
                traverse(node.right)
                
        traverse(self.root)
        return {"nodes": nodes, "edges": edges}

    # --- 旋转操作 (带快照) ---
    def right_rotate(self, y):
        x = y.left
        T2 = x.right
        
        # 记录旋转前的状态，高亮旋转轴心
        self.snapshot(f"准备对节点 {y.key} 进行右旋 (Right Rotate)...", highlight_nodes=[y.id, x.id])

        x.right = y
        y.left = T2
        
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        x.height = 1 + max(self.get_height(x.left), self.get_height(x.right))
        
        return x

    def left_rotate(self, x):
        y = x.right
        T2 = y.left
        
        # 记录旋转前的状态
        self.snapshot(f"准备对节点 {x.key} 进行左旋 (Left Rotate)...", highlight_nodes=[x.id, y.id])

        y.left = x
        x.right = T2
        
        x.height = 1 + max(self.get_height(x.left), self.get_height(x.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        
        return y

    # --- 插入逻辑 (带步骤记录) ---
    def insert_node(self, key):
        self.steps = [] # 清空之前的步骤
        self.snapshot(f"开始插入节点 {key}...")
        
        self.root = self._insert(self.root, key)
        
        self.snapshot(f"操作完成：树已平衡。", highlight_nodes=[str(key)])
        return self.steps # 返回步骤列表，而不是最终状态

    def _insert(self, node, key):
        if not node:
            return TreeNode(key)
        
        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else:
            return node 
            
        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        balance = self.get_balance(node)
        
        # 4种旋转情况检测
        
        # LL Case
        if balance > 1 and key < node.left.key:
            self.snapshot(f"发现失衡 (LL型): 节点 {node.key} 平衡因子为 {balance}", highlight_nodes=[node.id])
            return self.right_rotate(node)
            
        # RR Case
        if balance < -1 and key > node.right.key:
            self.snapshot(f"发现失衡 (RR型): 节点 {node.key} 平衡因子为 {balance}", highlight_nodes=[node.id])
            return self.left_rotate(node)
            
        # LR Case
        if balance > 1 and key > node.left.key:
            self.snapshot(f"发现失衡 (LR型): 节点 {node.key} 平衡因子为 {balance}", highlight_nodes=[node.id])
            node.left = self.left_rotate(node.left)
            return self.right_rotate(node)
            
        # RL Case
        if balance < -1 and key < node.right.key:
            self.snapshot(f"发现失衡 (RL型): 节点 {node.key} 平衡因子为 {balance}", highlight_nodes=[node.id])
            node.right = self.right_rotate(node.right)
            return self.left_rotate(node)
            
        return node
        
    def get_min_value_node(self, node):
        if node is None or node.left is None:
            return node
        return self.get_min_value_node(node.left)

    # --- 删除逻辑 (带步骤记录) ---
    def delete_node(self, key):
        self.steps = [] # 清空之前的步骤
        self.snapshot(f"开始删除节点 {key}...")
        
        self.root = self._delete(self.root, key)
        
        # 这里的 snapshot 可能会在 _delete 中树变空时稍微有些冗余，但作为结束标志很好
        self.snapshot(f"删除操作完成。", highlight_nodes=[])
        return self.steps

    def _delete(self, root, key):
        if not root:
            self.snapshot(f"未找到节点 {key}，无需删除。")
            return root

        # 1. 执行标准的 BST 删除
        if key < root.key:
            root.left = self._delete(root.left, key)
        elif key > root.key:
            root.right = self._delete(root.right, key)
        else:
            # 找到节点
            self.snapshot(f"找到节点 {key}，准备删除...", highlight_nodes=[root.id])
            
            # 情况 1 & 2: 只有一个子节点或无子节点
            if root.left is None:
                temp = root.right
                root = None
                return temp
            elif root.right is None:
                temp = root.left
                root = None
                return temp

            # 情况 3: 有两个子节点
            # 获取右子树中的最小值节点（中序后继）
            temp = self.get_min_value_node(root.right)
            
            self.snapshot(f"节点 {key} 有两个子节点，使用右子树最小节点 {temp.key} 替换它。", highlight_nodes=[root.id, temp.id])
            
            # 将后继节点的值复制当前节点
            root.key = temp.key
            # 为了保持 ID 唯一性 visuals mapping，通常简单的值替换会导致 ID 不对应的问题
            # 但在这个简单的演示里，我们假设 ID 是 str(key)。
            # 如果仅仅改 key，ID 没变，Vis.js 不会认为它是新节点。
            # 更好的做法是逻辑上删掉 temp，但如果为了动画连贯，值替换是最简单的。
            # 我们更新 ID 以匹配新的 key，虽然这在严谨的 OOP 里不好，但在 Visualization 里可以让 Vis.js 重绘它
            old_id = root.id
            root.id = str(temp.key) # 更新 ID
            
            # 删除中序后继
            root.right = self._delete(root.right, temp.key)

        if root is None:
            return root

        # 2. 更新高度
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        # 3. 检查平衡因子
        balance = self.get_balance(root)

        # 4. 如果失衡，进行旋转
        # LL Case
        if balance > 1 and self.get_balance(root.left) >= 0:
            self.snapshot(f"删除后发现失衡 (LL型): 节点 {root.key}", highlight_nodes=[root.id])
            return self.right_rotate(root)

        # LR Case
        if balance > 1 and self.get_balance(root.left) < 0:
            self.snapshot(f"删除后发现失衡 (LR型): 节点 {root.key}", highlight_nodes=[root.id])
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)

        # RR Case
        if balance < -1 and self.get_balance(root.right) <= 0:
            self.snapshot(f"删除后发现失衡 (RR型): 节点 {root.key}", highlight_nodes=[root.id])
            return self.left_rotate(root)

        # RL Case
        if balance < -1 and self.get_balance(root.right) > 0:
            self.snapshot(f"删除后发现失衡 (RL型): 节点 {root.key}", highlight_nodes=[root.id])
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root
        
    def reset(self):
        self.root = None
        self.steps = []
        return self.to_json()