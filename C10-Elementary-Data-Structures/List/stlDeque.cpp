#include <deque>
#include <iostream>
using namespace std;

int main() {
    deque<int> intDqe;
    ostream_iterator<int> screen(cout, " ");
    
    // 从双端队列的尾部添加元素
    intDqe.push_back(13);
    intDqe.push_back(75);
    intDqe.push_back(28);
    intDqe.push_back(35);
    
    // 输出到控制台
    copy(intDqe.begin(),intDqe.end(),screen);
    cout << endl;
    
    // 从双端队列的首部添加元素
    intDqe.push_front(0);
    intDqe.push_front(1);
    intDqe.push_front(2);
    intDqe.push_back(100);
    
    // 输出到控制台
    copy(intDqe.begin(),intDqe.end(),screen);
    cout << endl;
    
    // 从首部删除两个元素
    intDqe.pop_front();
    intDqe.pop_front();
    
    // 输出到控制台
    copy(intDqe.begin(),intDqe.end(),screen);
    cout << endl;
    
    // 从尾部删除两个元素
    intDqe.pop_back();
    intDqe.pop_back();
    
    // 输出到控制台
    copy(intDqe.begin(),intDqe.end(),screen);
    cout << endl;
    
    return 0;
}