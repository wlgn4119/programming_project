#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_menu();
void print_difficulty();
void print_how_to_play();
void generate_answer(int answer[], int len);
int  is_valid(int input[], int len);
int  count_strike(int answer[], int input[], int len);
int  count_ball(int answer[], int input[], int len);
void print_history(int history[][4], int sb[][2], int count, int len);
void run_game(int len, int max_try, int diff, int best[]);
void print_records(int best[]);

int main() {
    srand(time(NULL));

    int best[3] = {0, 0, 0};
    int menu;

    while (1) {
        print_menu();
        
        printf("메뉴 선택 => ");
        
        if (scanf("%d", &menu) != 1) {
            
            printf("잘못된 입력입니다.\n");
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (menu) {
            case 1: {
                
                int diff;
                
                print_difficulty();
                printf("난이도 선택 => ");

                if (scanf("%d", &diff) != 1)
                {
                    printf("\n잘못된 입력입니다.\n");

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                int c;
                while ((c = getchar()) != '\n' && c != EOF);

                if (diff == 1) run_game(3, 9, 0, best);      // 쉬움
                else if (diff == 2) run_game(3, 7, 1, best);      // 보통
                else if (diff == 3) run_game(4, 7, 2, best);      // 어려움
                else if (diff != 0) printf("\n잘못된 입력입니다.\n");
                
                break;
            }
            case 2:
                print_how_to_play();
                break;
            case 3:
                print_records(best);
                break;
            case 0:
                printf("\n게임을 종료합니다.\n");
                return 0;
            default:
                printf("\n잘못된 입력입니다.\n");
        }
    }
    return 0;
}

void print_menu()  // 메인 메뉴 출력, 작성자 : 신해인
{
    printf("\n=======================================\n");
    printf("          숫자 야구 게임\n");
    printf("=======================================\n");
    printf("  1. 게임 시작\n");
    printf("  2. 게임 방법\n");
    printf("  3. 최고 기록\n");
    printf("  0. 종료\n");
    printf("=======================================\n");
}

void print_difficulty()  // 난이도 선택 화면 출력, 작성자 : 신해인
{
    printf("\n=======================================\n");
    printf("          난이도 선택\n");
    printf("=======================================\n");
    printf("  1. 쉬움   - 3자리 /  9번 기회\n");
    printf("  2. 보통   - 3자리 /  7번 기회\n");
    printf("  3. 어려움 - 4자리 /  7번 기회\n");
    printf("  0. 돌아가기\n");
    printf("=======================================\n");
}

void print_how_to_play()  // 게임 방법 출력, 작성자 : 신해인
{
    printf("\n=======================================\n");
    printf("             게임 방법\n");
    printf("=======================================\n");
    printf("  컴퓨터가 중복 없는 숫자로 정답을 생성합니다.\n\n");
    printf("  [ 판정 기준 ]\n");
    printf("  Strike : 숫자, 자릿수 모두 일치\n");
    printf("  Ball   : 숫자는 맞지만 자릿수 불일치\n");
    printf("  Out    : 정답에 포함된 숫자 없음\n\n");
    printf("  [ 예시 ] 정답 : 3 1 5\n");
    printf("  3 2 7  =>  1 Strike  0 Ball\n");
    printf("  1 3 5  =>  1 Strike  2 Ball\n");
    printf("  2 4 6  =>  Out\n");
    printf("  3 1 5  =>  3 Strike  -> 승리!\n\n");
    printf("  [ 입력 규칙 ]\n");
    printf("  1~9 사이 숫자, 중복 불가\n");
    printf("=======================================\n");
    printf(" 엔터를 누르면 메인 메뉴로 돌아갑니다.\n");
    printf("=======================================\n");
    getchar();
}

void generate_answer(int answer[], int len)  // 정답 생성, 작성자 : 왕지후
{
    int used[10] = {0}; 
    int i = 0;
    while (i < len) {
        int num = rand() % 9 + 1; 
        if (used[num] == 0) {     
            answer[i] = num;
            used[num] = 1;
            i++;
        }
    }
}


int is_valid(int input[], int len)  // 입력값 유효성 검사, 작성자 : 왕지후
{
    int used[10] = {0};
    for (int i = 0; i < len; i++) {
        if (input[i] < 1 || input[i] > 9) return 0; 
        if (used[input[i]] == 1)           return 0; 
        used[input[i]] = 1;
    }
    return 1;
}

int count_strike(int answer[], int input[], int len)  // 스트라이크 개수 계산, 작성자 : 유기현
{
    int strike = 0;
    for (int i = 0; i < len; i++) {
        if (answer[i] == input[i]) strike++;
    }
    return strike;
}

int count_ball(int answer[], int input[], int len)  // 볼 개수 계산, 작성자 : 유기현
{
    int ball = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            
            if (i != j && input[i] == answer[j]) ball++;
        }
    }
    return ball;
}

void print_history(int history[][4], int sb[][2], int count, int len)  // 시도 기록 출력, 작성자 : 유기현
{
    printf("\n  시도 | 입력     | 결과\n");
    printf("  -----|----------|-------------------\n");
    for (int i = 0; i < count; i++) {
        printf("  %3d  | ", i + 1);
        for (int j = 0; j < len; j++) printf("%d ", history[i][j]);
        printf("  | ");
        if (sb[i][0] == 0 && sb[i][1] == 0)
            printf("Out\n");
        else
            printf("%d Strike  %d Ball\n", sb[i][0], sb[i][1]);
    }
    printf("  -----|----------|-------------------\n");
}

void run_game(int len, int max_try, int diff, int best[])  // 게임 진행, 작성자 : 왕지후
{

    int answer[4];
    int input[4];
    int history[9][4];
    int sb[9][2];
    int try_count = 0;

    generate_answer(answer, len);

    while (try_count < max_try) {

        printf("\n=======================================\n");
        printf("          숫자 야구 게임\n");
        printf("      남은 기회 : %d번\n", max_try - try_count);
        printf("=======================================\n");

        if (try_count > 0)
            print_history(history, sb, try_count, len);

        int valid = 0;
        while (!valid) {
            printf("숫자 입력 (%d자리) => ", len);
            int success = 1;
            for (int i = 0; i < len; i++)
            {
                if(scanf("%d", &input[i]) != 1)  // *****
                {
                    success = 0;
                    break;
                }
            }
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if(!success)
            {
                printf("  잘못된 입력입니다. 다시 입력하세요.\n");
                 continue;
            }
            if (is_valid(input, len))
                valid = 1;
            else
                printf("  잘못된 입력입니다. 다시 입력하세요.\n");
        }

        int strike = count_strike(answer, input, len);
        int ball   = count_ball(answer, input, len);

        for (int i = 0; i < len; i++) history[try_count][i] = input[i];
        sb[try_count][0] = strike;
        sb[try_count][1] = ball;
        try_count++;

        if (strike == len) {
            printf("\n=======================================\n");
            printf("          ★ 정 답 ! ★\n");
            printf("=======================================\n");
            printf("  시도  : %d번 만에 성공!\n", try_count);
            if (best[diff] == 0 || try_count < best[diff]) {
                best[diff] = try_count;
                printf("  ★ 최고 기록 갱신!\n");
            }
            printf("=======================================\n");
            return;
        }
    }

    printf("\n=======================================\n");
    printf("          게임 종료\n");
    printf("=======================================\n");
    printf("  기회를 모두 소진했습니다.\n");
    printf("  정답은 ");
    for (int i = 0; i < len; i++) printf("%d ", answer[i]);
    printf("였습니다.\n");
    printf("=======================================\n");
}

void print_records(int best[])  // 최고 기록 출력, 작성자 : 신해인
{
    char diff_name[3][15] = {"쉬움", "보통", "어려움"};
    printf("\n=======================================\n");
    printf("          최고 기록\n");
    printf("=======================================\n");
    printf("  난이도   | 최고 기록\n");
    printf("  ---------|----------\n");
    for (int i = 0; i < 3; i++) {
        if (best[i] == 0)
            printf("  %-10s | 기록 없음\n", diff_name[i]);
        else
            printf("  %-10s | %d번\n", diff_name[i], best[i]);
    }
    printf("=======================================\n");
    printf("  엔터를 누르면 메인 메뉴로 돌아갑니다.\n");
    printf("=======================================\n");
    getchar();
}