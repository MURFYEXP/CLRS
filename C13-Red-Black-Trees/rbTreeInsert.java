//2-3树的插入操作，与2-3-4树的插入的区别在于：2-3树先插入，再分裂（down）、调整（up）；2-3-4树先分裂（down），再插入、调整（up）。因此2-3-4树叫top-down，而2-3树叫bottom-up
public class RedBlackTree<Key extends Comparable<Key>, Value> {
    private static final int RED = 1;
    private static final int BLACK = 0;
    
    private class Node {
        Key key;
        Value value;
        Node left;
        Node right;
        int color;
        
        Node(Key key, Value value, int color) {
            this.key = key;
            this.value = value;
            this.color = color;
        }
    }
    
    private Node root;
    
    public void insert(Key key, Value value) {
        root = put(root, key, value);
    }
    
    //2-3-4树的插入
    private Node put0(Node node, Key key, Value value) {
        // 创建一个新的红色的节点
        if(node == null) {
            return new Node(key, value, RED);
        }
        
        //先分裂，再插入
        if(isRed(node.left) && isRed(node.right)) {
            return flipColor(node);
        }
        
        // 定位到需要插入的节点
        int compare = key.compareTo(node.key);
        if(compare < 0) {
            node.left = put(node.left, key, value);
        } else if(compare > 0) {
            node.right = put(node.right, key, value);
        } else {
            node.value = node.value;
            return node;
        }
        
        // 调整红黑树，使其平衡
        if(isRed(node.right) && !isRed(node.left)) {
            return rotateLeft(node);
        }
        if(isRed(node.left) && isRed(node.left.left)) {
            return rotateRight(node);
        }
        
        return node;
    }
    
    //2-3树的插入
    private Node put(Node node, Key key, Value value) {
        // 创建一个新的红色的节点
        if(node == null) {
            return new Node(key, value, RED);
        }
        
        // 先插入，再分裂
        // 定位到需要插入的节点
        int compare = key.compareTo(node.key);
        if(compare < 0) {
            node.left = put(node.left, key, value);
        } else if(compare > 0) {
            node.right = put(node.right, key, value);
        } else {
            node.value = node.value;
            return node;
        }
        
        // 调整红黑树，使其平衡
        if(isRed(node.right) && !isRed(node.left)) {
            return rotateLeft(node);
        }
        if(isRed(node.left) && isRed(node.left.left)) {
            return rotateRight(node);
        }
        if(isRed(node.left) && isRed(node.right)) {
            return flipColor(node);
        }
        
        return node;
    }
    
    private boolean isRed(Node node) {
        // 空节点属于黑节点
        if(node == null) return false;
        
        // 判断节点是否为红色
        return node.color == RED;
    }
    
    private Node rotateLeft(Node node) {
        Node right = node.right;
        node.right = right.left;
        right.left = node;
        int color = right.color;
        right.color = node.color;
        node.color = color;
        return right;
    }
    
    private Node rotateRight(Node node) {
        Node left = node.left;
        node.left = left.right;
        left.right = node;
        int color = left.color;
        left.color = node.color;
        node.color = color;
        return left;
    }
    
    private Node flipColor(Node node) {
        node.color = RED;
        node.left.color = BLACK;
        node.right.color = BLACK;
        return node;
    }
    
    public Value get(Key key) {
        Node node = root;
        while(node != null) {
            int compare = key.compareTo(node.key);
            if(compare < 0) {
                node = node.left;
            } else if(compare > 0) {
                node = node.right;
            } else {
                return node.value;
            }
        }
        // 没有找到
        return null;  
    }  
}  
