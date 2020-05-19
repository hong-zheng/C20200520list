// 6th 1:05之前没有听讲
// 带头双向循环链表
#include <stdio.h>
#include <stdlib.h>
typedef int Type ;
typedef struct Node {
	Type _data ;
	struct Node* _next ;
	struct Node* _prev ;
}Node ;

typedef struct List {
	Node* _header ;
}List ;
Node* createNode( Type data ) {
	Node* node = (Node*)malloc(sizeof(Node)) ;
	node->_data = data ;
	node->_prev = node->_next = NULL ;
	return node ;
}

void listInit( List* lst ) {
	// 创建一个头节点，构成循环结构
	Node* node = createNode(0) ;
	lst->_header = node ;
	lst->_header->_prev = lst->_header ;
	lst->_header->_next = lst->_header ;
}

void listPushBack( List* lst , Type data ) {
	Node* node = createNode( data ) ;
	Node* last = lst->_header->_prev ;
	
	// last node _header
	last->_next = node ;
	node->_prev = last ;
	
	node->_next = lst->_header ;
	lst->_header->_prev = node ;
}
void listPopBack( List* lst ) {
	// 注意：不能删除header
	if ( lst->_header->_next == lst->_header ) {
		return ;
	}

	Node* last = lst->_header->_prev ;
	Node* prev = last->_prev ;
	// prev _header 
	prev->_next = lst->_header ;
	lst->_header->_prev = prev ;
	free(last) ;
}

void listPushFront( List* lst , Type data ) {
	Node* node = createNode( data ) ;
	Node* head = lst->_header->_next ;
	lst->_header->_next = node ;
	node->_prev= lst->_header ;
	
	node->_next = head ;
	head->_prev= node ;
}
void listPopFront( List* lst ) {
	if ( lst->_header->_next == lst->_header ) {
		return ;
	}
	Node *front,*next ;
	front = lst->_header->_next ;
	next = front->_next ;
	free( front ) ;
	lst->_header->_next = next ;
	next->_prev = lst->_header ;
}
// 给当前数据前面插入一个数据
void listInsert(Node*pos , Type data) {
	Node* prev = pos->_prev ;
	Node* node = createNode( data ) ;
	// prev node pos
	prev->_next = node ;
	node->_prev = prev ;
	
	node->_next = pos ;
	pos->_prev = node ;
}
void listErase( Node* pos ) {
/*
	if ( lst->_header->_next == lst->_header )
		return ;
*/
	if ( pos->_next == pos ) return ;
	Node* prev = pos->_prev ;
	Node* last = pos->_next ;
	free( pos) ;
	prev->_next = last ;
	last->_prev = prev ;
}

void listPrint( List* lst ) {
	if ( !lst || !lst->_header) return ;
	Node* cur = lst->_header->_next ;
	while( cur != lst->_header ) {
		printf( "%d " , cur->_data ) ;
		cur = cur->_next ;
	} 
	printf("   end\n") ;
}
void listDestory( List* lst) {
/*
	if ( lst->_header->_next == lst->_header) {
		free( lst->_header ) ;
		return ;
	}
*/
	Node* cur = lst->_header->_next ;
	while( cur != lst->_header ) {
		Node* next = cur->_next ;
		free( cur ) ;
		cur = next ;
	}
	free( cur ) ;
	lst->_header = NULL ;
	printf("list is destoryed!\n") ;
}
void test() {
	List lst ;
	listInit( &lst ) ;
	listPushBack( &lst , 1 ) ;
	listPushBack( &lst , 2 ) ;
	listPushBack( &lst , 3 ) ;
	listPrint( &lst ) ;
	listPopFront( &lst ) ;
	listPrint( &lst ) ;
	listPushBack( &lst , 4 ) ;
	listPushFront( &lst , 5 ) ;
	listPrint( &lst ) ;
	listPopBack( &lst ) ;
	listPrint( &lst ) ;
	listPopBack( &lst ) ;
	listPrint( &lst ) ;
	listPopBack( &lst ) ;
	listPrint( &lst ) ;
	listPopBack( &lst ) ;
	listPrint( &lst ) ;
	
}
int main( void ) {
	test() ;
	return 0 ;
}
