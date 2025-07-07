// It was my first C program - quite rudimentary now,
// but undeniably the little program that sparked my love for coding.
// Author: Rainey
// Completed: 2023-05-06
// Write Note Date: 2025-07-07
#include <stdio.h>
#define ROWS 9
#define COLS 13
#define TRUE 1
// 1504教室的数据
int A[ROWS][COLS] = {{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 1
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 2
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 3
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 4
                     {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},   // 5
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 6
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 7
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 8
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}};  // 9

// 4207教室的数据
int B[ROWS][COLS] = {{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 1
                     {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},   // 2
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 3
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 4
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 5
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 6
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 7
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},   // 8
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}};  // 9

// 教室是否可以用的判断函数
int seat_usable(int room_num, int row, int col) {
  if (row < 1 || row > 9 || col < 1 || col > 13) return 0;
  switch (room_num) {
    case 1504:
      if (A[row - 1][col - 1]) return 0;
      break;
    case 4207:
      if (B[row - 1][col - 1]) return 0;
      break;
    default:
      return 0;
  }
  return 1;
}

// 输出座位布局函数
void show_seats(int room_num, int stu_num, int row, int col) {
  // 判断输入不合法的情况
  if (stu_num < 1 || stu_num > 97) {
    printf("error");
    return;  // 总人数不正确
  }
  if (!seat_usable(room_num, row, col)) {
    printf("error");
    return;  // 教室号输入错误、第一位同学的位置处于柱头或者过道上面
  }
  if (((row - 1) * (COLS - 2) + col - 2) > stu_num) {
    printf("error");
    return;  // 第一位同学的位置太大，不能从第一个位置开始排满座位表
  }

  // 初始化数据
  int seats[9][13];
  int row_seat = row;
  int col_seat = col;
  int hallway = 0;

  // 设定第一个座位的位置
  seats[row_seat - 1][col_seat - 1] = 1;

  // 填充座位表,向右填充
  switch (room_num) {
    case 1504:

      for (int a = 1; a <= stu_num; a++) {
        // 消去过道的存在引起的对人数判断的影响
        if (col_seat <= 3) {
          hallway = 0;
        }
        if (col_seat >= 4 && col_seat <= 10) {
          hallway = 1;
        }
        if (col_seat >= 10) {
          hallway = 2;
        }

        // 过道柱头检查
        if (A[row_seat - 1][col_seat - 1] == 1) {
          a--;  // 该位置不赋值，a减1;
          seats[row_seat - 1][col_seat - 1] = 0;
          if (col_seat == COLS) {
            seats[row_seat - 1][col_seat - 1] = 0;
            col_seat = 1;
            row_seat++;

            continue;
          }
          col_seat++;
          continue;
        }

        // 人数范围检查
        // 输入的首位同学的位置行大于5
        if (row >= 6) {
          if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
              stu_num) {  // hallway是过道，2代表有2个柱头，1代表本身的位置
            seats[row_seat - 1][col_seat - 1] = a;
            row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
            col_seat = 1;
            if (a == stu_num) {
              continue;
            }
            a--;
            continue;
          }
        }
        // 输入的首位同学的位置行等于于5
        else if (row == 5) {
          if (row_seat == 5) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 1 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat >= 6) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          }
        }
        // 输入的首位同学的位置行小于5
        else if (row <= 4) {
          if (row_seat <= 4) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway) == stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat == 5) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 1 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat >= 6) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          }
        }

        // 列满
        if (col_seat == COLS) {
          seats[row_seat - 1][col_seat - 1] = a;
          col_seat = 1;
          row_seat++;

          continue;
        }
        // 座位号赋值
        if (A[row_seat - 1][col_seat - 1] == 0) {
          seats[row_seat - 1][col_seat - 1] = a;
          col_seat++;
        }
      }

      // 打印座位表
      int status = 0;
      int BARRIER = 0;
      if (stu_num <= 11) {
        BARRIER = 0;
      } else if (stu_num > 11 && stu_num < 21) {
        BARRIER = 1;
      } else if (stu_num >= 21) {
        BARRIER = 2;
      }

      for (int i = 0, j2 = 0, a = 0; i <= ROWS; i++) {
        if (status == 1) {
          break;
        }
        for (int j = 0; j < COLS; j++) {
          if (j <= 2) {
            hallway = 0;
          } else if (j > 2 && j < 9) {
            hallway = 1;
          } else if (j >= 9) {
            hallway = 2;
          }
          // 每个数字占两个字符，空格补位，每列数字右对齐 : printf("%2d",
          // seats[i][j]);
          // 行尾的不可用座位或者过道不显示空格或者任何字符;
          // 与前一个座位的间隔也不显示空格;
          if (seats[i][j] != 0) {
            printf("%2d", seats[i][j]);
            if (j != 12 && seats[i][j + 1] != 0) {
              if ((i * 11 + j - BARRIER) != stu_num) {
                printf(" ");
              }
            }
          }
          if (j == 3 || j == 9) {
            printf(" ");
          }
          // 不可用座位显示为两个空格
          if (seats[i][j] == 0) {
            if (j != 12) {
              printf("   ");  // 行尾不打印 "  ";
            }
          }
          // 每一行行尾仅有一个\n
          a++;
          if (a % 13 == 0) {
            printf("\n");
            continue;
          }

          j2 = j;
          if (stu_num <= 44) {
            if ((i) * (COLS - 2) + j - hallway == stu_num) {
              status = TRUE;
              break;
            }
          } else if (stu_num > 44 && stu_num < 54) {
            if ((i) * (COLS - 2) + j - hallway - 1 == stu_num) {
              status = TRUE;
              break;
            }
          } else if (stu_num >= 54) {
            if ((i) * (COLS - 2) + j - hallway - 1 == stu_num) {
              status = TRUE;
              break;
            }
          }
        }
      }

      break;
    case 4207:
      for (int a = 1; a <= stu_num; a++) {
        // 消去过道的存在引起的对人数判断的影响
        if (col_seat <= 3) {
          hallway = 0;
        }
        if (col_seat >= 4 && col_seat <= 10) {
          hallway = 1;
        }
        if (col_seat >= 10) {
          hallway = 2;
        }

        // 过道柱头检查
        if (B[row_seat - 1][col_seat - 1] == 1) {
          a--;  // 该位置不赋值，a减1;
          seats[row_seat - 1][col_seat - 1] = 0;
          if (col_seat == COLS) {
            seats[row_seat - 1][col_seat - 1] = 0;
            col_seat = 1;
            row_seat++;

            continue;
          }
          col_seat++;
          continue;
        }

        // 人数范围检查
        // 输入的首位同学的位置行大于2
        if (row >= 3) {
          if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
              stu_num) {  // hallway是过道，2代表有2个柱头，1代表本身的位置
            seats[row_seat - 1][col_seat - 1] = a;
            row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
            col_seat = 1;
            if (a == stu_num) {
              continue;
            }
            a--;
            continue;
          }
        }
        // 输入的首位同学的位置行等于于2
        else if (row == 2) {
          if (row_seat == 2) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 1 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat >= 3) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;  // 将赋值位转移至班级数组的第一个位置;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          }
        }
        // 输入的首位同学的位置行小于2
        else if (row == 1) {
          if (row_seat == 1) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway) == stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat == 2) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 1 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          } else if (row_seat >= 3) {
            if (((row_seat - 1) * (COLS - 2) + col_seat - hallway - 2 - 1) ==
                stu_num) {
              seats[row_seat - 1][col_seat - 1] = a;
              row_seat = 1;
              col_seat = 1;
              if (a == stu_num) {
                continue;
              }
              a--;
              continue;
            }
          }
        }

        // 列满
        if (col_seat == COLS) {
          seats[row_seat - 1][col_seat - 1] = a;
          col_seat = 1;
          row_seat++;

          continue;
        }
        // 座位号赋值
        if (B[row_seat - 1][col_seat - 1] == 0) {
          seats[row_seat - 1][col_seat - 1] = a;
          col_seat++;
        }
      }

      // 打印座位表
      int STATUS = 0;
      int barrier = 0;
      if (stu_num <= 11) {
        barrier = 0;
      } else if (stu_num > 11 && stu_num < 21) {
        barrier = 1;
      } else if (stu_num >= 21) {
        barrier = 2;
      }

      for (int i = 0, j2 = 0, a = 0; i <= ROWS; i++) {
        if (STATUS == 1) {
          break;
        }
        for (int j = 0; j < COLS; j++) {
          if (j <= 2) {
            hallway = 0;
          } else if (j > 2 && j < 9) {
            hallway = 1;
          } else if (j >= 9) {
            hallway = 2;
          }

          // 每个数字占两个字符，空格补位，每列数字右对齐 : printf("%2d",
          // seats[i][j]);
          // 行尾的不可用座位或者过道不显示空格或者任何字符;
          // 与前一个座位的间隔也不显示空格;
          if (seats[i][j] != 0) {
            printf("%2d", seats[i][j]);
            if (j != 12 && seats[i][j + 1] != 0) {
              if ((i * 11 + j - barrier) != stu_num) {
                printf(" ");
              }
            }
          }
          if (j == 3 || j == 9) {
            printf(" ");
          }
          // 不可用座位显示为两个空格
          if (seats[i][j] == 0) {
            if (j != 12&&(i*11+j-barrier-1)!=stu_num) {
              printf("   ");  // 行尾不打印 "  ";
            }
          }
          // 每一行行尾仅有一个\n
          a++;
          if (a % 13 == 0) {
            printf("\n");
            continue;
          }

          j2 = j;
          if (stu_num <= 11) {
            if ((i) * (COLS - 2) + j - hallway == stu_num) {
              STATUS = TRUE;
              break;
            }
          } else if (stu_num > 11 && stu_num < 21) {
            if ((i) * (COLS - 2) + j - hallway - 1 == stu_num) {
              STATUS = TRUE;
              break;
            }
          } else if (stu_num >= 21) {
            if ((i) * (COLS - 2) + j - hallway - 1 == stu_num) {
              STATUS = TRUE;
              break;
            }
          }
        }
      }
      break;
    default:
      break;
  }
}

int main() {
  int room_num, stu_num, row, col;
  scanf("%d %d %d %d", &room_num, &stu_num, &row, &col);
  show_seats(room_num, stu_num, row, col);
  return 0;
}