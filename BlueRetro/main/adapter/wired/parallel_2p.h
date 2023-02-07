/*
 * Copyright (c) 2019-2022, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PARA_2P_H_
#define _PARA_2P_H_
#include "adapter/adapter.h"

void para_2p_meta_init(struct generic_ctrl *ctrl_data);
void para_2p_init_buffer(int32_t dev_mode, struct wired_data *wired_data);
void para_2p_from_generic(int32_t dev_mode, struct generic_ctrl *ctrl_data, struct wired_data *wired_data);
void para_2p_gen_turbo_mask(uint32_t index, struct wired_data *wired_data);

#endif /* _PARA_2P_H_ */
