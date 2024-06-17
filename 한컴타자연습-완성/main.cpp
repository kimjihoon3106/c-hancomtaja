#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SENTENCE_LENGTH 100
#define NUM_SENTENCES 15
#define WORD_COUNT 100
#define GRID_SIZE 16
#define DISPLAY_TIME 5
#define MAX_NAME_LENGTH 50
#define RANKING_FILE "ranking.txt"

void generate_random_words(char words[WORD_COUNT][20]);
void shuffle_words(char words[WORD_COUNT][20]);
void display_grid(char grid[GRID_SIZE][20]);
void hide_grid();
int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining);
void update_ranking(const char* name, int score);
void show_ranking();

const char* sentences[NUM_SENTENCES] = {
    "java를 빨리 자바.",
    "한글은 아름다운 언어입니다.",
    "프로그래밍은 재미있습니다.",
    "C 언어는 강력한 프로그래밍 언어입니다.",
    "컴퓨터 과학은 흥미로운 분야입니다.",
    "코드는 살아 움직이는 예술이다.",
    "어떤 문제든 해결할 수 있는 방법은 존재한다",
    "코드는 더 좋은 개발자를 만든다.",
    "좋은 코드는 좋은 문서보다 낫다. 그러나 좋은 문서 없이 좋은 코드는 없다.",
    "만약 당신이 버그를 찾지 못했다면, 당신은 아직 충분히 찾지 않은 것이다.",
    "가장 좋은 프로그래머는 그들이 쓴 코드를 최대한 짧게 유지하는 사람이다.",
    "코드를 쓸 때는 사람이 이해하기 쉽도록 작성하라.",
    "좋은 프로그래밍은 훌륭한 스토리텔링과 같다. 간결하고 명확해야 한다.",
    "코딩은 언어의 미학이다.",
    "어떤 것을 만들어내는 것은 당신의 코드가 아니라 그것이 하는 일이다."
};

void generate_random_words(char words[WORD_COUNT][20]) {
    const char* sample_words[WORD_COUNT] = {
        "사과", "바나나", "체리", "대추", "엘더베리", "무화과", "포도", "허니듀",
        "키위", "레몬", "망고", "넥타린", "오렌지", "파파야", "모과", "산딸기",
        "딸기", "귤", "우글리", "바닐라", "수박", "참외", "황금열매", "호박",
        "살구", "블랙베리", "멜론", "용과", "에그프루트", "페이조아", "자몽",
        "허클베리", "임베", "잭프루트", "금귤", "라임", "멜론", "넥타", "올리브",
        "복숭아", "쿠아라리베아", "로완", "구아바", "토마토", "우니", "보아방가",
        "울프베리", "자몽", "유자", "자두", "감", "밤", "매실", "모과", "자두",
        "살구", "수수", "복분자", "살구", "다래", "자두", "감귤", "배", "참다래",
        "수박", "참외", "토마토", "참다래", "자두", "감", "배", "다래", "참외",
        "참다래", "수박", "참외", "복분자", "배", "참외", "수박", "참외", "복분자",
        "살구", "자두", "매실", "자두", "배", "다래", "참다래", "복분자", "자두",
        "수박", "참외", "복분자", "매실", "자두", "다래", "수박", "참외", "다래"
    };

    for (int i = 0; i < WORD_COUNT; i++) {
        strcpy(words[i], sample_words[i]);
    }
}

void shuffle_words(char words[WORD_COUNT][20]) {
    srand((unsigned int)time(NULL));
    for (int i = WORD_COUNT - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[20];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

void display_grid(char grid[GRID_SIZE][20]) {
    printf("단어 그리드:\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%s ", grid[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
}

void hide_grid() {
    system("cls");
    printf("5초가 지나 그리드가 가려졌습니다.\n");
}

int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (strcmp(grid[i], word) == 0) {
            strcpy(grid[i], "");  // 단어를 맞췄을 때 빈 문자열로 바꿔서 다시 맞추지 못하게 함
            (*remaining)--;
            return 1;
        }
    }
    return 0;
}

void update_ranking(const char* name, int score) {
    FILE* file = fopen(RANKING_FILE, "a+");
    if (file == NULL) {
        printf("랭킹 파일을 열 수 없습니다.\n");
        return;
    }

    char line[100];
    char player_name[MAX_NAME_LENGTH];
    int player_score;
    int found = 0;

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("임시 파일을 생성할 수 없습니다.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d", player_name, &player_score);
        if (strcmp(player_name, name) == 0) {
            if (score > player_score) {
                fprintf(temp_file, "%s %d\n", name, score);
            }
            else {
                fprintf(temp_file, "%s %d\n", player_name, player_score);
            }
            found = 1;
        }
        else {
            fprintf(temp_file, "%s %d\n", player_name, player_score);
        }
    }

    if (!found) {
        fprintf(temp_file, "%s %d\n", name, score);
    }

    fclose(file);
    fclose(temp_file);

    remove(RANKING_FILE);
    rename("temp.txt", RANKING_FILE);
}

void show_ranking() {
    FILE* file = fopen(RANKING_FILE, "r");
    if (file == NULL) {
        printf("랭킹 파일을 열 수 없습니다.\n");
        return;
    }

    char line[100];
    printf("전체 랭킹:\n");
    printf("------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void typing_test_1(const char* nickname) {
    srand(time(NULL));
    time_t start_time, current_time;
    char input_text[MAX_SENTENCE_LENGTH];
    int correct_entries = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30) {
        int sentence_index = rand() % NUM_SENTENCES;
        const char* test_sentence = sentences[sentence_index];

        printf("다음 문장을 입력하세요:\n\033[30m\033[47m%s\n\033[0m", test_sentence);

        printf("입력 대기 중... (남은 시간: %d초)\n", 30 - (int)difftime(current_time, start_time));
        fflush(stdout);

        // 입력 대기 루프
        int retval = 0;
        while (retval == 0 && difftime(current_time, start_time) < 30) {
            if (_kbhit()) {
                fgets(input_text, MAX_SENTENCE_LENGTH, stdin);
                retval = 1;
            }
            else {
                Sleep(100); // 100밀리초 대기
            }
            time(&current_time);
        }

        if (retval) {
            // 입력한 문장의 끝에 있는 '\n' 제거
            size_t len = strlen(input_text);
            if (len > 0 && input_text[len - 1] == '\n') {
                input_text[len - 1] = '\0';
            }

            if (strcmp(input_text, test_sentence) == 0) {
                correct_entries++;
                printf("정확하게 입력했습니다.\n\n");
            }
            else {
                printf("잘못 입력했습니다. 다시 시도하세요.\n\n");
            }
        }
        else {
            printf("시간 초과!\n");
            break;
        }

        time(&current_time);
        int remaining_time = 30 - (int)difftime(current_time, start_time);
        printf("남은 시간: %d초\n", remaining_time);
        fflush(stdout);

        if (remaining_time <= 0) {
            printf("시간 초과!\n");
            break;
        }
    }

    // 파일을 읽기 모드로 열기
    FILE* fp = fopen("rankings.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 기존 엔트리 구조체 정의
    typedef struct {
        char nickname[50];
        int correct_entries;
    } Entry;

    Entry entries[NUM_SENTENCES];
    int num_entries = 0;

    // 파일에서 엔트리 읽어오기
    while (fscanf(fp, "%s\t%d\n", entries[num_entries].nickname, &entries[num_entries].correct_entries) != EOF) {
        num_entries++;
    }

    fclose(fp);

    // 기존 별명 검색 및 점수 업데이트
    int nickname_found = 0;
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].nickname, nickname) == 0) {
            if (entries[i].correct_entries < correct_entries) {
                entries[i].correct_entries = correct_entries;
            }
            nickname_found = 1;
            break;
        }
    }

    // 새로운 별명이면 엔트리에 추가
    if (!nickname_found) {
        strcpy(entries[num_entries].nickname, nickname);
        entries[num_entries].correct_entries = correct_entries;
        num_entries++;
    }

    // 파일을 쓰기 모드로 열기
    fp = fopen("rankings.txt", "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일에 엔트리 쓰기
    for (int i = 0; i < num_entries; i++) {
        fprintf(fp, "%s\t%d\n", entries[i].nickname, entries[i].correct_entries);
    }

    fclose(fp);

    printf("30초 동안 올바르게 입력한 횟수: %d\n", correct_entries);

    printf("\n");
    system("pause");
}

void typing_test_2() {
    srand(time(NULL));
    int sentence_index = rand() % NUM_SENTENCES;
    const char* test_sentence = sentences[sentence_index];

    char input_text[MAX_SENTENCE_LENGTH];
    time_t start_time, end_time;

    printf("입력할 문장: %s\n", test_sentence);

    time(&start_time);
    printf("문장을 입력하고 엔터를 누르세요: ");
    fgets(input_text, MAX_SENTENCE_LENGTH, stdin);
    time(&end_time);

    // 입력한 문장의 끝에 있는 '\n' 제거
    size_t len = strlen(input_text);
    if (len > 0 && input_text[len - 1] == '\n') {
        input_text[len - 1] = '\0';
    }

    double elapsed_time = difftime(end_time, start_time);
    int correct_chars = 0;
    for (int i = 0; i < strlen(test_sentence); i++) {
        if (input_text[i] == test_sentence[i]) {
            correct_chars++;
        }
    }
    double accuracy = (double)correct_chars / strlen(test_sentence) * 100.0;

    printf("입력 시간: %.2f초\n", elapsed_time);
    printf("정확도: %.2f%%\n", accuracy);
    printf("속도: %.2f chars/sec\n", strlen(input_text) / elapsed_time);

    printf("\n");
    system("pause");
}

void view_rankings() {
    FILE* fp = fopen("rankings.txt", "r");
    if (fp == NULL) {
        printf("랭킹 파일을 열 수 없습니다.\n");
        return;
    }

    printf("\n전체 랭킹:\n");
    printf("------------\n");

    // 엔트리 구조체 정의
    typedef struct {
        char nickname[50];
        int correct_entries;
    } Entry;

    Entry entries[NUM_SENTENCES];
    int num_entries = 0;

    // 파일에서 엔트리 읽어오기
    while (fscanf(fp, "%s\t%d\n", entries[num_entries].nickname, &entries[num_entries].correct_entries) != EOF) {
        num_entries++;
    }

    fclose(fp);

    // 정확한 입력 횟수에 따라 정렬하기 (내림차순)
    for (int i = 0; i < num_entries - 1; i++) {
        for (int j = i + 1; j < num_entries; j++) {
            if (entries[i].correct_entries < entries[j].correct_entries) {
                Entry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // 정렬된 엔트리 출력하기
    for (int i = 0; i < num_entries; i++) {
        printf("%d위: %s - %d 점\n", i + 1, entries[i].nickname, entries[i].correct_entries);
    }

    printf("\n");
    system("pause");
}

void reset_rankings() {
    FILE* fp = fopen("rankings.txt", "w");
    if (fp == NULL) {
        printf("랭킹 파일을 열 수 없습니다.\n");
        return;
    }
    fclose(fp);
    printf("랭킹이 초기화되었습니다.\n");
}

void reset_rankings2() {
    FILE* fp = fopen("ranking.txt", "w");
    if (fp == NULL) {
        printf("랭킹 파일을 열 수 없습니다.\n");
        return;
    }
    fclose(fp);
    printf("랭킹이 초기화되었습니다.\n");
}

int main() {
    char words[WORD_COUNT][20];
    char grid[GRID_SIZE][20];
    char input[20];
    int score = 0;
    int choice;
    char nickname[50];

    while (1) {
        printf("       지훈이의 한컴타자연습\n");
        system("pause");
        clear_terminal();

        printf("별명을 입력하세요: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = '\0'; // 개행 문자 제거

        clear_terminal();

        while (1) {
            int choice;

            printf("     ------지훈이의 한컴타자------\n");

            printf("     1. 30초 타이핑 테스트\n");
            printf("     2. 문장 타이핑 테스트\n");
            printf("     3. 단어 기억 타이핑 게임\n");
            printf("     4. 해상 구조\n");
            printf("     5. 물고기 잡기\n");
            printf("     6. 개발자 노트\n");
            printf("     7. 랭킹 보기\n");
            printf("     8. 관리자 모드\n");
            printf("     9. 로그아웃\n");
            printf("     10. 프로그램 종료\n");

            printf("     --------------------------\n");
            printf("     선택하세요: ");
            scanf("%d", &choice);
            getchar();  // '\n' 문자를 제거

            switch (choice) {
                case 1:
                {
                    clear_terminal();
                    typing_test_1(nickname);
                    clear_terminal();
                    break;
                }
                case 2:
                {
                    clear_terminal();
                    typing_test_2();
                    clear_terminal();
                    break;
                }
                case 3:
                {
                    clear_terminal();
                    generate_random_words(words);
                    shuffle_words(words);

                    for (int i = 0; i < GRID_SIZE; i++) {
                        strcpy(grid[i], words[i]);
                    }

                    display_grid(grid);
                    Sleep(DISPLAY_TIME * 1000);
                    hide_grid();

                    int remaining = GRID_SIZE;

                    while (1) {
                        printf("단어를 입력하세요 (끝을 입력하면 종료): ");
                        scanf("%s", input);

                        if (strcmp(input, "끝") == 0) {
                            break;
                        }

                        if (is_word_in_grid(grid, input, &remaining)) {
                            printf("맞았습니다!\n");
                            score++;
                            printf("남은 단어 수: %d\n", remaining);
                        }
                        else {
                            printf("틀렸습니다.\n");
                        }
                    }
                    printf("게임 종료! 점수: %d\n", score);
                    update_ranking(nickname, score);
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 4:
                {
                    clear_terminal();
                    printf("     개발 중 입니다. 다시 선택하세요.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 5:
                {
                    clear_terminal();
                    printf("     개발 중 입니다. 다시 선택하세요.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 6:
                {
                    clear_terminal();
                    printf("     개발 중 입니다. 다시 선택하세요.\n\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                case 10:
                {
                    printf("     프로그램을 종료합니다.\n");
                    return 0;
                }
                case 7:
                {
                    clear_terminal();

                    int number;
                    printf("     --------------------------\n");
                    printf("     1. 30초 타이핑 테스트 랭킹.\n");
                    printf("     2. 단어 기억 타이핑 게임 랭킹.\n");
                    printf("     --------------------------\n");
                    printf("     선택하세요: ");
                    scanf("%d", &number);
                    getchar();

                    switch (number) {
                    case 1:
                        clear_terminal();
                        view_rankings();
                        clear_terminal();
                        break;
                    case 2:
                        clear_terminal();
                        show_ranking();
                        system("pause");
                        clear_terminal();
                        break;
                    }
                    break;
                }
                case 8:
                {
                    clear_terminal();
                    char admin_password[20];
                    printf("관리자 비밀번호를 입력하세요: ");
                    fgets(admin_password, sizeof(admin_password), stdin);
                    admin_password[strcspn(admin_password, "\n")] = '\0'; // 개행 문자 제거

                    if (strcmp(admin_password, "abcd") == 0) {
                        clear_terminal();
                        int admin_choice;
                        printf("관리자 모드에 접속하였습니다.\n");
                        printf("     --------------------------\n");
                        printf("     1.30초 타이핑 테스트 랭킹 초기화\n");
                        printf("     2.단어 기억 타이핑 게임 랭킹 초기화\n");
                        printf("     3. 돌아가기\n");
                        printf("     --------------------------\n");
                        printf("     선택하세요: ");
                        scanf("%d", &admin_choice);
                        getchar();  // '\n' 문자 제거

                        switch (admin_choice) {
                        case 1:
                            clear_terminal();
                            reset_rankings();
                            clear_terminal();
                            break;
                        case 3:
                            clear_terminal();
                            printf("관리자 모드에서 돌아갑니다.\n");
                            break;
                        case 2:
                            clear_terminal();
                            reset_rankings2();
                            clear_terminal();
                            break;
                        default:
                            printf("잘못된 선택입니다. 관리자 모드를 종료합니다.\n");
                            break;
                        }
                    }
                    else {
                        printf("잘못된 비밀번호입니다. 관리자 모드 접근이 거부되었습니다.\n");
                    }

                    system("pause");
                    clear_terminal();
                    break;
                }
                case 9:
                {
                    clear_terminal();
                    printf("로그아웃합니다.\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                default:
                {
                    clear_terminal();
                    printf("     잘못된 선택입니다. 다시 선택하세요.\n");
                    system("pause");
                    clear_terminal();
                    break;
                }
                if (choice == 9) {
                    break; // 로그아웃하여 별명을 다시 입력 받기 위해 내부 while 루프 탈출
                }
            }
        }
    }
}
