//
// Created by jkhu29 on 2021/5/2.
//

#ifndef EELAB_DEMO_RETARGET_H
#define EELAB_DEMO_RETARGET_H

#include "stm32f1xx_hal.h"
#include <sys/stat.h>
#include <stdio.h>

void RetargetInit(UART_HandleTypeDef *huart);

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

int _fstat(int fd, struct stat *st);

#endif //EELAB_DEMO_RETARGET_H
