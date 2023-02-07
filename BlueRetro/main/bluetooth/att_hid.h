/*
 * Copyright (c) 2019-2022, Jacques Gagnon
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _BT_ATT_HID_H_
#define _BT_ATT_HID_H_

void bt_att_hid_init(struct bt_dev *device);
void bt_att_write_hid_report(struct bt_dev *device, uint8_t report_id, uint8_t *data, uint32_t len);
void bt_att_hid_hdlr(struct bt_dev *device, struct bt_hci_pkt *bt_hci_acl_pkt, uint32_t len);

#endif /* _BT_ATT_HID_H_ */
