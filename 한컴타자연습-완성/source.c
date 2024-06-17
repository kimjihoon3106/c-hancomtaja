#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX_SENTENCE_LENGTH 100
#define NUM_SENTENCES 15

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

void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typing_test_1() {
    srand(time(NULL));
    time_t start_time, current_time;
    char input_text[MAX_SENTENCE_LENGTH];
    int correct_entries = 0;

    time(&start_time);
    current_time = start_time;

    while (difftime(current_time, start_time) < 30) {
        int sentence_index = rand() % NUM_SENTENCES;
        const char* test_sentence = sentences[sentence_index];

        printf("다음 문장을 입력하세요:\n%s\n", test_sentence);

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
                printf("정확하게 입력했습니다.\n");
            }
            else {
                printf("잘못 입력했습니다. 다시 시도하세요.\n");
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

int main() {
    printf("       지훈이의 한컴타자연습\n");

    while (1) {
        int choice;

        printf("     --------------------------\n");

        printf("     1. 30초 타이핑 테스트\n");
        printf("     2. 문장 타이핑 테스트\n");
        printf("     3. 케이크 던지기\n");
        printf("     4. 해상 구조\n");
        printf("     5. 물고기 잡기\n");
        printf("     6. 개발자 노트\n");
        printf("     7. 프로그램 종료\n");

        printf("     --------------------------\n");
        printf("     선택하세요: ");
        scanf("%d", &choice);
        getchar();  // '\n' 문자를 제거

        switch (choice) {
        case 1:
            clear_terminal();
            typing_test_1();
            clear_terminal();
            break;
        case 2:
            clear_terminal();
            typing_test_2();
            clear_terminal();
            break;
        case 3:
            printf("     개발 중 입니다. 다시 선택하세요.\n");
            break;
        case 4:
            printf("     개발 중 입니다. 다시 선택하세요.\n");
            break;
        case 5:
            printf("     개발 중 입니다. 다시 선택하세요.\n");
            break;
        case 6:
            printf("     작성 중 입니다. 다시 선택하세요.\n");
            break;
        case 7:
            printf("     프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("     잘못된 선택입니다. 다시 선택하세요.\n");
            break;
        }
    }

    return 0;
}
