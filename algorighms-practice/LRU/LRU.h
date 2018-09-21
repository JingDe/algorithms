
LRU算法

CacheLRU<string, PartialCacheInfo>** m_block_caches;
一个存储 string的key——cache数据结构 的采用LRU算法的 类似map结构


Countn是用来计算存储的元素Data的大小
template < class T >
struct Countn {
		unsigned long operator()( const T &x ) { return 1; }
};

template< class Key, class Data, class Sizefn = Countn< Data > > class CacheLRU
存储的内容
std::list<std::pair<Key, Data> >

所有key
std::vector<Key>

索引
std::map<Key, list的迭代器>

成员
List: LRUcache的存储内容
Map: std::map<Key, list的迭代器>， 用来快速索引cache
cache的最大大小，当前大小
////
每个内存块的大小
未使用的内存块的指针list，内存块的链表


思考：
空间是固定的吗？
添加：空间不足时，如何淘汰？
删除
查找、访问：如何更新最近使用情况？
通过map的查找，加速list的查找？


<>初始化分配指定个数的内存块
<>更新
将list的被访问元素插入到list的开头，splice


_touch(Key)，将list中key匹配的元素，移动到list的开头，并返回begin迭代器
通过map将key查到list的迭代器
同时要更新map中该key对应的迭代器//通过map的迭代器


<>
_remove(Key)由key在map中查找
_remove(map的迭代器)
map迭代器获得map的second元素，即list的迭代器，获得list存储的cache结构
回收该cache的内存指针，即插入到未使用指针链表
删除list中元素
删除map中元素

remove(Key)实现：
将一个cache从list中删除，将内存回收到指针链表中

<>
insert_and_fetch<Key, Data, >
currsize初始化0
maxsize初始化指定的内存块的个数，未使用内存指针链表的元素个数

当currsize超过maxsize：
删除list最后一个元素，remove(最后的key)

将新节点插入到list开头
更新currsize
// currsize和maxsize控制不超过初始配置的内存块个数

赋予元素/cache一个引用计数的属性，只删除引用计数为0的元素





