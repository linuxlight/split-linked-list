

// Node : 리스트에 하나씩 추가될 데이터의 형태를 정의
typedef struct Node {
    char* data;
    struct Node* prev; // 이전 노드를 가리킬 포인터
    struct Node* next; // 다음 노드를 가리킬 포인터
} Node;

// LinkedList : 단순 연결 리스트를 정의
typedef struct {
    Node* head; // 리스트의 시작 노드를 지정할 포인터
    int size; // 리스트의 노드 갯수를 저장할 변수
} LinkedList;




// CDLL_List_Init : 환형 이중 연결리스트를 초기화 하는 함수
LinkedList* CDLL_List_Init() {
    // 리스트를 선언
    LinkedList* newList;
    // 리스트의 메모리를 Heap 영역에 할당
    newList = (LinkedList*)malloc(sizeof(LinkedList));
    // 새로운 리스트의 head와 size의 값을 초기화
    newList->head = NULL;
    newList->size = 0;
    return newList;
}




// CDLL_Node_Init : 리스트에 들어갈 노드를 초기화하는 함수
Node* CDLL_Node_Init(char* str) {
    // 새로운 노드와, 노드의 문자열 데이터의 메모리를 Heap영역에 할당
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(str)+1);
    // str의 값을 새로운 노드의 데이터에 복사
    strcpy(newNode->data, str);
    // 새로운 노드의 포인터를 설정
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}




// CDLL_findFastRoot : 빠른 경로로 n번째 노드까지 이동하는 함수
// 예를들어 단순 연결리스트에서 마지막 노드로 가려면
// head 노드부터 next를 반복해 여러 노드를 거쳐야 함.
// 하지만 환형 이중 연결리스트에서는 head에서 prev 한번만 가면 됨
// 이 함수는 prev 혹은 next로 빠르게 n번 노드까지 이동하고 주소를 반환
Node* CDLL_findFastRoot(LinkedList* list, int n) {
    Node* selectNode = list->head;
    int totalNodes = list->size;
    int median = totalNodes >> 1; // 비트 연산 나누기 2 (중앙값)
    int i;

    // n가 노드의 중앙값 이하일 경우 next로 이동
    if(n <= median) {
        printf("next -> %d\n",n);
        for(i=0;i<n;i++) {
            selectNode = selectNode->next;
        }
    }
    // n가 노드 중앙값보다 클경우 prev로 이동
    else {
        printf("prev <- %d\n",totalNodes-n);
        for(i=0;i< totalNodes-n; i++) {
            selectNode = selectNode->prev;
        }
    }

    return selectNode;
}




// CDLL_insertLastNode : 리스트의 끝에 노드를 추가하는 함수
void CDLL_insertLastNode(LinkedList* list, char* str) {
    // 새로운 노드를 생성하고 newNode 변수에 할당
    Node* newNode = CDLL_Node_Init(str);

    // 리스트에 노드가 없는 경우
    if (list->head == NULL) {
        // 리스트의 head를 새로운 노드로 설정하고
        list->head = newNode;
        // (중요!) next와 prev를 자기 자신으로 설정
        newNode->next = newNode;
        newNode->prev = newNode;
    }
    // 리스트에 노드가 있는경우
    else {
        // 새로운 노드의 prev와 next를 설정
        newNode->prev = list->head->prev;
        newNode->next = list->head;
        // 현재의 마지막 노드의 next를 newNode로 설정
        // 즉 마지막 노드를 newNode로 설정
        list->head->prev->next = newNode;
        list->head->prev = newNode;
    }
    list->size++;
}

// CDLL_insertNodeAt : 리스트의 head로부터 n번째 위치에 노드를 추가
void CDLL_insertNodeAt(LinkedList* list, char* str, int n) {
    Node* newNode;
    // selectNode : 리스트의 노드를 선택하기 위한 변수. 리스트의 head부터 시작
    Node* selectNode = list->head;

    // 리스트에 노드가 없거나 인수 n의 값이 올바르지 않을 경우
    if(list->size == 0 || n < 0 || list->size-1 < n) {
        // 리스트의 마지막에 노드를 추가후 종료
        CDLL_insertLastNode(list, str);
        return;
    }

    // 새로운 노드를 초기화 해주고 newNode에 담아줌
    newNode = CDLL_Node_Init(str);    
    // 0번 즉 head 부분에 노드를 삽입
    if(n==0) {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head = newNode;
    }
    // n번째 노드 자리에 새로운 노드를 삽입
    else {
        // findFastRoot함수로 삽입할 부분에 있는 노드를 지정
        selectNode = CDLL_findFastRoot(list,n);
        newNode->next = selectNode;
        newNode->prev = selectNode->prev;
        selectNode->prev->next = newNode;
        selectNode->prev = newNode;
    }
    list->size++;
}




// CDLL_removeLastNode : 리스트의 마지막 노드를 삭제하는 함수
void CDLL_removeLastNode(LinkedList* list) {
    Node* selectNode = list->head;

    // 리스트에 노드가 없는 경우 함수를 종료
    if (list->head == NULL) return;

    // 리스트에 노드가 하나인 경우 head 지정된 노드를 제거
    if (list->head->next == list->head) {
        list->head = NULL;
    }
    // 리스트에 노드가 두개인 경우 
    else if(list->head->next == list->head->prev) {
        selectNode = list->head->next;
        list->head->next = list->head;
        list->head->prev = list->head;
    }
    // 리스트에 노드가 세개 이상인 경우
    else {
        selectNode = list->head->prev;
        list->head->prev = list->head->prev->prev;
        list->head->prev->next = list->head;
    }
    free(selectNode->data);
    free(selectNode);
    list->size--;
}

// CDLL_removeNodeAt : 리스트의 head로부터 n번째 위치의 노드를 삭제
void CDLL_removeNodeAt(LinkedList* list, int n) {
    // selectNode : 리스트의 노드를 선택하기 위한 변수. 리스트의 head부터 시작
    Node* selectNode = list->head;
    int totalNodes = list->size;

    // 리스트에 노드가 없거나 인수 n의 값이 올바르지 않을 경우
    if(list->head == NULL || n < 0 || totalNodes-1 < n) {
        return;
    }
    // 0번 즉 head 부분의 노드를 삭제하는 경우
    if(n==0) {
        selectNode = list->head;
        list->head->next->prev = list->head->prev;
        list->head->prev->next = list->head->next;
        list->head = list->head->next;
    }
    // 그 외의 노드를 삭제하는 경우
    else {
        selectNode = CDLL_findFastRoot(list,n);
        selectNode->prev->next = selectNode->next;
        selectNode->next->prev = selectNode->prev;
    }
    free(selectNode->data);
    free(selectNode);
    list->size--;
}





// CDLL_searchNodes : str과 일치하는 데이터가 head로부터 몇번째 위치에 있는지 확인
void CDLL_searchNodes(LinkedList* list, char* str) {
    // access[] : 위치를 저장할 배열을 생성 (같은 내용의 데이터가 있을수도 있으니)
    int access[100] = {-1};
    int accessCount = 0, nodeN = 0;
    Node* s_prevNode = list->head->prev;
    Node* s_nextNode = list->head;
    int loopCount = list->size%2 ? (list->size>>1)+1 : list->size>>1;

    // head와 head->prev부터 next, prev로 한칸씩 이동하며 배열 탐색
    // 예를들어 5칸의 배열의 경우 0,4 -> 1,3 -> 2 와 같은 순으로 탐색
    for(int i=1; i<=loopCount; i++) {
        //printf("N: %s\n",s_nextNode->data);
        if(!strcmp(s_nextNode->data,str)) {
            access[accessCount] = nodeN;
            access[accessCount+1] = -1;
            accessCount++;
        }
        // 노드의 갯수가 홀수일 경우 마지막 값을 중복 탐색하므로 break해줌
        if(i == loopCount && list->size%2 == 1) {
            break;
        }
        //printf("P: %s\n",s_prevNode->data);
        if(!strcmp(s_prevNode->data,str)) {
            access[accessCount] = list->size - i;
            access[accessCount+1] = -1;
            accessCount++;
        }
        s_prevNode = s_prevNode->prev;
        s_nextNode = s_nextNode->next;
        nodeN++;
    }

    // 탐색 결과를 출력
    // access에 값이 들어가지 않았을시 해당 데이터가 없음을 출력
    if(access[0] == -1) {
        printf("%s Not Found!\n\n",str);
    }
    // 데이터가 있을시 해당 데이터가 head로부터 몇번째 next에 있는지 출력
    else {
        for(int i=0; i<100; i++) {
            if(access[i] == -1) {
                break;
            } else {
                printf("%d ",access[i]);
            }
        }
        printf("\n\n");
    }
}







// CDLL_printList : 리스트 안 모든 노드의 데이터를 표시
void CDLL_printList(LinkedList* list) {
    Node *selectNode = list->head;
    int i;
    printf("List = ");

    // 리스트의 사이즈를 이용하여 리스트를 력력
    for(i=0; i<list->size; i++) {
        printf("%s",selectNode->data);
        selectNode = selectNode->next;
        if(i != list->size-1) {
            printf(", ");
        }
    }
    printf(" (Total = %d)\n",list->size);

    printf("\n");
} 

// CDLL_destoryList : 리스트 안의 모든 노드와, 리스트의 메모리를 해제
void CDLL_destroyList(LinkedList* list) {
    Node *delNode = list->head;
    
    if(list->head != NULL) {
        list->head->prev->next = NULL;
        
        while(delNode != NULL) {
            delNode->prev = NULL;
            list->head = delNode->next;
            free(delNode->data);
            free(delNode);
            delNode = list->head;
        }
    }
    free(list);
}








int main() {
    LinkedList* party;

    party = CDLL_List_Init();
    
    printf("Create the list\n");
    CDLL_printList(party);

    printf("Add two nodes\n");
    CDLL_insertLastNode(party,"Ali");
    CDLL_insertLastNode(party,"Joly");
    CDLL_printList(party);

    printf("Insert Chris node at 1 \n");
    CDLL_insertNodeAt(party,"Chris",1);
    CDLL_printList(party); 

    printf("Insert Ali node at 0 \n");
    CDLL_insertNodeAt(party,"Ali",0);
    CDLL_printList(party); 

    printf("Search Ali\n");
    CDLL_searchNodes(party,"Ali");

    printf("Remove node at 2\n");
    CDLL_removeNodeAt(party,2);
    CDLL_printList(party);

    printf("Remove node at 0\n");
    CDLL_removeNodeAt(party,0);
    CDLL_printList(party);

    printf("Remove the last node\n");
    CDLL_removeLastNode(party);
    CDLL_printList(party);

    CDLL_destroyList(party);

    return 0;
}