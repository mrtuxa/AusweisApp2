/*!
 * \copyright Copyright (c) 2015-2019 Governikus GmbH & Co. KG, Germany
 */

#include "messages/BluetoothMessageDisconnectResponse.h"

using namespace governikus;

BluetoothMessageDisconnectResponse::BluetoothMessageDisconnectResponse()
	: BluetoothMessage(BluetoothMsgId::DisconnectResponse)
{
}


BluetoothMessageDisconnectResponse::~BluetoothMessageDisconnectResponse()
{
}
