from flask import Flask, render_template, request, jsonify
from avl_core import AVLTree

app = Flask(__name__)
avl_system = AVLTree()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/insert', methods=['POST'])
def api_insert():
    data = request.json
    try:
        key = int(data.get('value'))
    except ValueError:
        return jsonify({"status": "error", "message": "请输入有效的整数"})
    
    # 获取步骤列表
    steps = avl_system.insert_node(key)
    
    return jsonify({
        "status": "success",
        "steps": steps 
    })

@app.route('/api/delete', methods=['POST'])
def api_delete():
    data = request.json
    try:
        key = int(data.get('value'))
    except ValueError:
        return jsonify({"status": "error", "message": "请输入有效的整数"})
    
    # 获取步骤列表
    steps = avl_system.delete_node(key)
    
    return jsonify({
        "status": "success",
        "steps": steps 
    })

@app.route('/api/reset', methods=['POST'])
def api_reset():
    data = avl_system.reset()
    return jsonify({
        "status": "success", 
        "data": data
    })

if __name__ == '__main__':
    app.run(debug=True, port=5000)