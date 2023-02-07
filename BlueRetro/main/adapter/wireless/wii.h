/*
 * Copyright (c) 2019-2020, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WII_H_
#define _WII_H_
#include "adapter/adapter.h"

int32_t wii_to_generic(struct bt_data *bt_data, struct generic_ctrl *ctrl_data);
void wii_fb_from_generic(struct generic_fb *fb_data, struct bt_data *bt_data);

#endif /* _WII_H_ */
