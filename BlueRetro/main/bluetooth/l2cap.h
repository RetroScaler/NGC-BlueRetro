/*
 * Copyright (c) 2019-2020, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _BT_L2CAP_H_
#define _BT_L2CAP_H_

void bt_l2cap_init_dev_scid(struct bt_dev *device);
void bt_l2cap_cmd_ext_feat_mask_req(void *bt_dev);
void bt_l2cap_cmd_sdp_conn_req(void *bt_dev);
void bt_l2cap_cmd_hid_ctrl_conn_req(void *bt_dev);
void bt_l2cap_cmd_hid_intr_conn_req(void *bt_dev);
void bt_l2cap_cmd_sdp_disconn_req(void *bt_dev);
void bt_l2cap_cmd_hid_ctrl_disconn_req(void *bt_dev);
void bt_l2cap_cmd_hid_intr_disconn_req(void *bt_dev);
void bt_l2cap_sig_hdlr(struct bt_dev *device, struct bt_hci_pkt *bt_hci_acl_pkt);
void bt_l2cap_le_sig_hdlr(struct bt_dev *device, struct bt_hci_pkt *bt_hci_acl_pkt, uint32_t len);

#endif /* _BT_L2CAP_H_ */
