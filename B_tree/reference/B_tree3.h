
//B树的定义之一

#define  m  3   // B树的阶，此设为
typedef struct 
{
    KeyType  key;
    char     data;
} Record;

typedef struct BTNode 
{
    int             keynum;        // 结点中关键字个数，即结点的大小
    struct BTNode  *parent;        // 指向双亲结点
    KeyType         key[m + 1];      // 关键字向量，0号单元未用
    struct BTNode  *ptr[m + 1];      // 子树指针向量
//  Record         *recptr[m + ];   // 记录指针向量，0号单元未用
                                      //在此添加其他自定义数据
} BTNode, *BTree;                // B树结点和B树的类型
