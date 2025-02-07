/**
 * Copyright (c) 2017-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick
import QtQuick.Controls
import Governikus.EnterPasswordView
import Governikus.Global
import Governikus.PasswordInfoView
import Governikus.Style
import Governikus.TitleBar
import Governikus.Type.ApplicationModel
import Governikus.Type.NumberModel
import Governikus.Type.PasswordType
import Governikus.Type.RemoteServiceModel

Item {
	id: baseItem

	implicitHeight: mainColumn.implicitHeight

	QtObject {
		id: d

		property bool oldLockedAndHiddenStatus
	}
	Column {
		id: mainColumn

		readonly property int usableWidth: width - leftPadding - rightPadding

		spacing: Constants.component_spacing
		width: baseItem.width

		GOptionsContainer {
			containerPadding: Constants.pane_padding
			//: LABEL ANDROID IOS
			title: qsTr("Paired devices")
			visible: availablePairedDeviceList.count > 0
			width: parent.usableWidth

			ListView {
				id: availablePairedDeviceList

				height: childrenRect.height
				interactive: false
				model: RemoteServiceModel.availablePairedDevices
				spacing: Constants.component_spacing
				width: parent.width

				delegate: DevicesListDelegate {
					//: LABEL ANDROID IOS
					description: qsTr("Available")
					linkInactive: !isNetworkVisible
					linkQuality: linkQualityInPercent
					title: remoteDeviceName
					width: availablePairedDeviceList.width

					onClicked: {
						deleteDevicePopup.deviceId = deviceId;
						deleteDevicePopup.deviceName = remoteDeviceName;
						deleteDevicePopup.open();
					}
				}
			}
		}
		GOptionsContainer {
			containerPadding: Constants.pane_padding
			//: LABEL ANDROID IOS
			title: qsTr("Last connected")
			visible: unavailablePairedDeviceList.count > 0
			width: parent.usableWidth

			ListView {
				id: unavailablePairedDeviceList

				height: childrenRect.height
				interactive: false
				model: RemoteServiceModel.unavailablePairedDevices
				spacing: Constants.component_spacing
				width: parent.width

				delegate: DevicesListDelegate {
					//: LABEL ANDROID IOS
					description: qsTr("Click to remove device")
					linkInactive: !isNetworkVisible
					linkQuality: linkQualityInPercent
					title: remoteDeviceName
					width: unavailablePairedDeviceList.width

					onClicked: {
						deleteDevicePopup.deviceId = deviceId;
						deleteDevicePopup.deviceName = remoteDeviceName;
						deleteDevicePopup.open();
					}
				}
			}
		}
		ConfirmationPopup {
			id: deleteDevicePopup

			property var deviceId
			property string deviceName

			//: INFO ANDROID IOS
			okButtonText: qsTr("Remove")
			//: INFO ANDROID IOS
			text: qsTr("Do you want to remove the pairing of the device \"%1\"?").arg(deviceName)

			//: INFO ANDROID IOS
			title: qsTr("Remove pairing")

			onConfirmed: RemoteServiceModel.forgetDevice(deviceId)
		}
		GOptionsContainer {
			containerPadding: Constants.pane_padding
			containerSpacing: Constants.component_spacing
			//: LABEL ANDROID IOS
			title: qsTr("Add pairing")
			width: parent.usableWidth

			GListView {
				id: searchDeviceList

				height: childrenRect.height
				model: RemoteServiceModel.availableDevicesInPairingMode
				spacing: Constants.component_spacing
				visible: ApplicationModel.wifiEnabled && count > 0
				width: parent.width

				delegate: DevicesListDelegate {
					//: LABEL ANDROID IOS
					description: qsTr("Click to pair")
					linkQuality: linkQualityInPercent
					title: remoteDeviceName + (isSupported ? "" : (" (" + remoteDeviceStatus + ")"))
					width: searchDeviceList.width

					onClicked: {
						if (isSupported && RemoteServiceModel.rememberServer(deviceId)) {
							d.oldLockedAndHiddenStatus = getLockedAndHidden();
							setLockedAndHidden();
							push(enterPinView);
						}
					}
				}
			}
			GText {
				//: INFO ANDROID IOS Wifi is not enabled and no new devices can be paired.
				text: qsTr("Please connect your WiFi to use another smartphone as card reader (SaC).")
				textStyle: Style.text.normal_warning
				visible: !ApplicationModel.wifiEnabled
				width: parent.width
			}
			GButton {
				anchors.horizontalCenter: parent.horizontalCenter

				//: LABEL ANDROID IOS
				text: qsTr("Enable WiFi")
				visible: !ApplicationModel.wifiEnabled

				onClicked: ApplicationModel.enableWifi()
			}
			LocalNetworkInfo {
				topPadding: Constants.component_spacing
				visible: RemoteServiceModel.requiresLocalNetworkPermission && !RemoteServiceModel.remoteReaderVisible
				width: parent.width
			}
			PairingProcessInfo {
				visible: !searchDeviceList.visible && ApplicationModel.wifiEnabled
				width: parent.width
			}
			RemoteServiceWifiInfo {
				visible: !searchDeviceList.visible && ApplicationModel.wifiEnabled
				width: parent.width
			}
		}
	}
	Component {
		id: enterPinView

		EnterPasswordView {
			function close() {
				setLockedAndHidden(d.oldLockedAndHiddenStatus);
				pop();
			}

			passwordType: PasswordType.REMOTE_PIN
			//: LABEL ANDROID IOS
			title: qsTr("Pairing code")

			navigationAction: NavigationAction {
				action: NavigationAction.Action.Cancel

				onClicked: close()
			}

			onPasswordEntered: close()
		}
	}
}
