/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
	taskCreate(shooterTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	delay(60000);
	lift();//raises lift, runs conveyer belt, shoots and lowers conveyer belt, hopefully

	//insert delays and calls to lift for entire period
}

void shooterTask(void *ignore) {
	//shooter takes ~3.5 seconds per launch
	shooter1->out = 127;
	shooter2->out = 127;
	shooter3->out = 127;
	//shoot ball 1
	conveyer->out = 127;
	delay(2000);
	conveyer->out = 0;
	delay(1500);
	//shoot ball 2
	conveyer->out = 127;
	delay(2000);
	conveyer->out = 0;
	delay(1500);
	//shoot ball 3
	conveyer->out = 127;
	delay(2000);
	conveyer->out = 0;
	delay(1500);
	//shoot ball 4
	conveyer->out = 127;
	delay(2000);
	conveyer->out = 0;
	delay(1500);

	taskSuspend(shooterTask);
}

void shoot() {
	conveyer->out = 127;
	delay(200);
	conveyer->out = 0;
	int shootPower = 127;

	shooter1->out = shootPower;
	shooter2->out = shootPower;
	shooter3->out = shootPower;

	delay(10000);

	shooter1->out = 0;
	shooter2->out = 0;
	shooter3->out = 0;
}

void lift() {
	int liftpower = 100;
	int count = 0;
	while (top->state != 0) {
		liftbottom->out = liftpower;
		liftleftm->out = liftpower;
		lifttop->out = liftpower;
		liftrightm->out = liftpower;
		count++;
	}
	shoot();
	for (int x = 0; x < count; x++) {
		liftbottom->out = -liftpower;
		liftleftm->out = -liftpower;
		lifttop->out = -liftpower;
		liftrightm->out = -liftpower;
	}

}

