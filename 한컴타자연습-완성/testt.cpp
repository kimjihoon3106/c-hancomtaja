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
#define ADMIN_PASSWORD "admin123"

void generate_random_words(char words[WORD_COUNT][20]);
void shuffle_words(char words[WORD_COUNT][20]);
void display_grid(char grid[GRID_SIZE][20]);
void hide_grid();
int is_word_in_grid(char grid[GRID_SIZE][20], char* word, int* remaining);
void update_ranking(const char* name, int score);
void show_ranking();
void typing_test(const char* nickname);
void word_game(const char* nickname);
void admin_mode();
void clear_terminal();

const char* sentences[NUM_SENTENCES] = {
    "java를 빨리 자바.",
    "한글은 아름다운 언어입니다.",
    "프로그래밍은 재미있습니다.",
    "C 언어는 강력한 프로그래밍 언어입니다.",
    "컴퓨터 과학은 흥미로운 분야입니다.",
    "코드는 살아 움직이는 예술이다.",
    "어떤 문제든 해결할 수 있는 방법은 존재한다.",
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
    clear_terminal();
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
    printf("랭킹:\n");
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

void typing_test(const char* nickname) {
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
                ("정확합니다!\n");
            }
            else {
                printf("틀렸습니다. 정답은 \"%s\"입니다.\n", test_sentence);
            }
        }
    }

    printf("타이핑 테스트가 종료되었습니다.\n");
    printf("%s님의 정확한 입력 횟수: %d\n", nickname, correct_entries);
    update_ranking(nickname, correct_entries);
}

void word_game(const char* nickname) {
    char words[WORD_COUNT][20];
    char grid[GRID_SIZE][20];
    int remaining = GRID_SIZE;

    generate_random_words(words);
    shuffle_words(words);

    // 단어 그리드 초기화
    for (int i = 0; i < GRID_SIZE; i++) {
        strcpy(grid[i], words[i]);
    }

    printf("단어 게임을 시작합니다. 그리드가 표시됩니다.\n");
    display_grid(grid);
    printf("5초 후에 그리드가 가려집니다.\n");

    Sleep(DISPLAY_TIME * 1000);  // 5초 대기

    hide_grid();

    time_t start_time, current_time;
    int correct_words = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30 && remaining > 0) {
        char input_word[20];
        printf("단어를 입력하세요: ");
        scanf("%s", input_word);

        if (is_word_in_grid(grid, input_word, &remaining)) {
            correct_words++;
            printf("정답입니다!\n");
        }
        else {
            printf("틀렸습니다.\n");
        }

        time(&current_time);
    }

    printf("단어 게임이 종료되었습니다.\n");
    printf("%s님의 정확힌 단어 입력 횟수: %d\n", nickname, correct_words);
    update_ranking(nickname, correct_words);
}

void admin_mode() {
    printf("관리자 모드에 진입하셨습니다.\n");
    printf("비밀번호를 입력하세요: ");

    char password[20];
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        int choice;
        do {
            printf("\n=== 관리자 메뉴 ===\n");
            printf("1. 랭킹 보기\n");
            printf("2. 랭킹 초기화\n");
            printf("3. 프로그램 종료\n");
            printf("메뉴를 선택하세요: ");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                show_ranking();
                break;
            case 2:
                remove(RANKING_FILE);
                printf("랭킹이 초기화되었습니다.\n");
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                exit(0);
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
            }
        } while (choice != 3);
    }
    else {
        printf("비밀번호가 일치하지 않습니다. 관리자 모드 접근이 거부되었습니다.\n");
    }
}

int main() {
    int menu_choice;
    char nickname[MAX_NAME_LENGTH];

    printf("환영합니다! 닉네임을 입력하세요: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;  // '\n' 제거

    do {
        printf("\n=== 메뉴 ===\n");
        printf("1. 타이핑 테스트 시작\n");
        printf("2. 단어 게임 시작\n");
        printf("3. 관리자 모드\n");
        printf("4. 로그아웃\n");
        printf("5. 프로그램 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &menu_choice);

        switch (menu_choice) {
        case 1:
            typing_test(nickname);
            break;
        case 2:
            word_game(nickname);
            break;
        case 3:
            admin_mode();
            break;
        case 4:
            printf("%s님, 로그아웃 되었습니다.\n", nickname);
            break;
        case 5:
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    } while (menu_choice != 4);

    return 0;
}

