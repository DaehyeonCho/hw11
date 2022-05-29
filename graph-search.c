#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define MAX_QUEUE_SIZE 100
#define TRUE 1
#define FALSE 0

/* vertex 구조 생성 */
typedef struct graphnode{
    int vertex;           // 데이터 필드
    struct graphnode* link;  // 링크 필드
}graphNode;

typedef struct graphtype{
    int n;      // vertex 개수 
    graphNode* adj_list[MAX_VERTEX];    // 헤드 포인터 저장하는 배열
}graphType;

int visited1[MAX_VERTEX];        // dfs 방문정보 저장 flag
int visited2[MAX_VERTEX];        // bfs 방문정보 저장 flag

typedef struct queuetype{
    int element[MAX_QUEUE_SIZE];
    int front, rear;
}queueType;

void initqueue(queueType* q);
void enqueue(queueType* q, int vertex);
int dequeue(queueType* q);
int is_empty(queueType* q);

void initialize(graphType* g);
void insertVertex(graphType* g);
void insertEdge(graphType* g, int x, int y);
void depthFirstSearch(graphType* g, int x);
void breathFirstSearch(graphType* g, int x);
void printGraph(graphType* g, int x);

int main(){
    char command;
    int x, y;
    graphType g;

    do{
        printf("\n");
        printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize             = z                                      \n");
		printf(" Insert Vertex          = v          Insert Edge             = e \n");
		printf(" Depth First Search     = d          Breath First Search     = b\n");
		printf(" Print Graph            = p          Quit                    = q\n");
		printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command){
        case 'z': case 'Z':
            initialize(&g);
            break;
        case 'v': case 'V':
            for(int i = 0; i < MAX_VERTEX; i++){
                insertVertex(&g);
            }
            break;
        case 'e': case 'E':
            printf("vertex 입력 : ");
            scanf("%d %d", &x, &y);
            insertEdge(&g, x, y);
            break;
        case 'd': case 'D':
            printf("vertex 입력 : ");
            scanf("%d", &x);
            depthFirstSearch(&g, x);
            break;
        case 'b': case 'B':
            printf("vertex 입력 : ");
            scanf("%d", &x);
            breathFirstSearch(&g, x);
            break;
        case 'p': case 'P':
            printf("vertex 입력 : ");
            scanf("%d", &x);
            printGraph(&g, x);
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
		    break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

void initialize(graphType* g){          // 그래프 초기화
    g->n = 0;
    for(int i = 0; i < MAX_VERTEX; i++){    
        g->adj_list[i] = NULL;
    }
}

void insertVertex(graphType* g){
    if(((g->n) + 1) > MAX_VERTEX){      // 최대 vertex 초과했을 때 오류 메시지 출력
        printf("vertex 개수 초과!\n");
        return;
    }

    g->n++;     // vertex 추가
}

void insertEdge(graphType* g, int x, int y){
    graphNode* node = (graphNode*)malloc(sizeof(graphNode));    // edge를 이을 vertex 노드 생성

    if(x >= g->n || y >= g->n){         // 그래프에 vertex가 없을 때 오류 메시지 출력
        printf("그래프에 없는 vertex입니다.\n");
        return;
    }

    node->vertex = y;       // vertex 노드에 새로 연결할 vertex 저장
    node->link = g->adj_list[x];    // 두 vertex 연결 
    g->adj_list[x] = node;
}

void depthFirstSearch(graphType* g, int x){
    graphNode* currnetNode; // 현재 vertex 가리키는 노드 생성

    visited1[x] = TRUE;   // 정점을 방문했으므로 방문정보 TRUE로 설정
    printf("%5d\n", x);

    for(currnetNode = g->adj_list[x]; currnetNode; currnetNode = currnetNode->link){
        if(!visited1[currnetNode->vertex])       // 방문하지 않은 곳이 없을 때까지 반복
            depthFirstSearch(g, currnetNode->vertex);
    }
}

void breathFirstSearch(graphType* g, int x){
    graphNode* currentNode;     // 현재 vertex 가리키는 노드 생성
    queueType q;                // 큐 생성
    initqueue(&q);


    printf("%5d\n", x); // 정점 출력
    visited2[x] = TRUE;  // 정점을 방문했으므로 방문정보 TRUE로 설정
    enqueue(&q, x);      // 큐에 삽입

    while(!is_empty(&q)){
        x = dequeue(&q); // 큐에서 방문한 vertex 제거
        for(currentNode = g->adj_list[x]; currentNode; currentNode = currentNode->link){
            if(!visited2[currentNode->vertex]){  // 방문하지 않은 곳이 없을 때까지 반복
                printf("%5d\n", currentNode->vertex);   // 다음 방문한 vertex 출력
                visited2[currentNode->vertex] = TRUE;    // 방문정보 TRUE로 설정
                enqueue(&q, currentNode->vertex);        // 큐에 삽입
            }
        }
    }
}

void printGraph(graphType* g, int x){
    graphNode* temp;

    printf("\n");
    printf("%d 노드와 연결된 vertex : ", x);

    if(g->adj_list[x] == NULL){     // 그래프가 비어있을 경우 오류 메시지 출력
        printf("공백 그래프\n");
    }

    for(temp = g->adj_list[x]; temp; temp = temp->link){    // 입력한 vertex와 인접한 vertex 출력
        printf("%d -> ", temp->vertex);
    }

}

/* 큐 삽입 함수 */
void enqueue(queueType* q, int vertex){    
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->element[q->rear] = vertex;
}

/* 큐 삭제 함수 */
int dequeue(queueType* q){         
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->element[q->front];
}

/* 큐 초기화 함수 */
void initqueue(queueType* q){
    q->front = q->rear = 0;
}

/* 큐 공백 상태 검출 함수 */
int is_empty(queueType* q){
    return (q->front == q->rear);
}