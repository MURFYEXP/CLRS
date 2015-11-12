//定义一个指针，使用之前必须分配内存空间
int main(int argc, const char * argv[])
{
    /*可读入空格符*/
    char str1[10];
    gets(str1);
    cout << str1 << endl;
    
    /*遇到空格符及结束*/
    //输入字符串方案一
    char str2[10]; //定义一个字符数组
    //输入字符串方案二
    string str3;   //定义一个字符串对象
    str3 = new string;   //直接分配内存空间
    //输入字符串方案三
    string astr = "lalala"; //定义一个字符串指针
    string *stri = &astr;//间接分配内存空间
    //输入字符串方案四
    cin  >> *stri;
    cout << *stri << endl;
    return 0;
}