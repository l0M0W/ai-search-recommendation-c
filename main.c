#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 5
#define MAX_STR 50

// 추천 콘텐츠 및 데이터베이스 구조체 정의
typedef struct {
    int id;
    char keyword[MAX_STR];    // 검색 매칭용 핵심 키워드
    char title[MAX_STR];      // 출력용 콘텐츠 제목
    int interest_weight;      // 사용자의 관심도 가중치 (AI 학습 지표)
} Content;

// 전체 콘텐츠 데이터베이스 초기화 (신용관리 지식 및 IT 트렌드 데이터 포함)
Content db[MAX_ITEMS] = {
    {1, "인공지능", "AI 트렌드 및 딥러닝 기초 가이드", 0},
    {2, "C언어", "C언어로 배우는 핵심 알고리즘과 자료구조", 0},
    {3, "신용관리", "재테크의 시작, 대학생 신용점수 올리는 법", 0},
    {4, "인공지능", "초거대 언어 모델(LLM)의 활용과 미래", 0},
    {5, "주식", "안정적인 자산 관리를 위한 우량주 투자 가이드", 0}
};

// 1. 즉시 검색 기능 함수
void instant_search() {
    char search_key[MAX_STR];
    int found = 0;
    
    printf("\n[즉시 검색] 검색어를 입력하세요: ");
    scanf("%s", search_key);
    
    printf("\n▶ '%s' 검색 결과:\n", search_key);
    for(int i = 0; i < MAX_ITEMS; i++) {
        // 입력한 키워드가 데이터베이스 내 키워드 또는 제목에 포함되어 있는지 검사
        if(strstr(db[i].keyword, search_key) != NULL || strstr(db[i].title, search_key) != NULL) {
            printf("- [%d] %s (현재 관심도 점수: %d)\n", db[i].id, db[i].title, db[i].interest_weight);
            
            // 사용자가 검색한 항목에 가중치를 누적시킴 (사용자 관심사 학습 과정)
            db[i].interest_weight += 5; 
            found = 1;
        }
    }
    if(!found) {
        printf("  검색 결과가 존재하지 않습니다.\n");
    }
}

// 2. 가중치 분석 기반 관심사 자동 추천 함수 (AI 학습 알고리즘)
void ai_recommendation() {
    printf("\n========================================\n");
    printf("🤖 AI 분석 기반 [당신을 위한 맞춤형 추천 콘텐츠]\n");
    printf("   (굳이 검색하지 않아도 당신의 누적 관심사를 바탕으로 추천합니다)\n");
    printf("========================================\n");
    
    int recommend_count = 0;
    
    // 관심도 가중치가 0보다 큰 항목(과거 검색 이력 기반 선호 항목)들을 우선적으로 상위 추천함
    for(int i = 0; i < MAX_ITEMS; i++) {
        if(db[i].interest_weight > 0) {
            printf("⭐️ [추천 지수: %d] %s (연관 키워드: %s)\n", 
                   db[i].interest_weight, db[i].title, db[i].keyword);
            recommend_count++;
        }
    }
    
    // 만약 누적된 검색 이력이 없어서 가중치가 전부 0일 경우, 기본 웰컴 가이드 콘텐츠 추천
    if(recommend_count == 0) {
        printf("💡 처음 방문하셨군요! 오늘의 추천 콘텐츠입니다:\n");
        printf("- %s (연관 키워드: %s)\n", db[0].title, db[0].keyword);
        printf("- %s (연관 키워드: %s)\n", db[2].title, db[2].keyword); // 신용관리 정보 기본 추천
    }
    printf("========================================\n");
}

int main() {
    int choice;
    
    printf("====================================================\n");
    printf("  🎓 AI 검색 및 개인 맞춤형 관심사 추천 시스템 v1.0\n");
    printf("====================================================\n");
    
    while(1) {
        printf("\n[메뉴] 1: 즉시 검색 | 2: AI 자동 추천 보기 | 3: 프로그램 종료\n");
        printf("선택: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            instant_search();
        } else if(choice == 2) {
            ai_recommendation();
        } else if(choice == 3) {
            printf("\n프로그램을 종료합니다. 과제를 마칩니다.\n");
            break;
        } else {
            printf("\n올바른 메뉴 번호를 선택해 주세요.\n");
        }
    }
    return 0;
}
