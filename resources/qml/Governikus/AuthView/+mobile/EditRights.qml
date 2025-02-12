/**
 * Copyright (c) 2016-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick
import QtQuick.Layouts
import Governikus.Global
import Governikus.Style
import Governikus.TitleBar
import Governikus.View
import Governikus.Type.AuthModel
import Governikus.Type.NumberModel
import Governikus.Type.CertificateDescriptionModel
import Governikus.Type.ChatModel

FlickableSectionPage {
	id: baseItem

	property alias actionText: actionText.text
	property alias dataText: dataPasswordText.text
	property var workflowModel: AuthModel

	signal rightsAccepted

	spacing: Constants.component_spacing

	//: LABEL IOS_PHONE ANDROID_PHONE
	title: qsTr("Identify")

	navigationAction: NavigationAction {
		action: NavigationAction.Action.Cancel

		onClicked: workflowModel.cancelWorkflow()
	}

	GText {
		id: actionText

		//: LABEL IOS_PHONE ANDROID_PHONE
		text: qsTr("You are about to identify yourself towards the following provider:")
	}
	GPane {
		Layout.fillWidth: true
		color: mouseArea.pressed ? Style.color.pane_active : Style.color.pane

		Item {
			Accessible.description: providerInfoSection.title + ". " + providerInfoSection.name + ". " + providerInfoAction.text
			Accessible.role: Accessible.Button
			height: providerEntries.height
			width: parent.width

			Accessible.onPressAction: mouseArea.clicked(null)

			Column {
				id: providerEntries

				spacing: Constants.groupbox_spacing

				anchors {
					left: parent.left
					right: forwardAction.left
					rightMargin: Constants.text_spacing
					top: parent.top
				}
				ProviderInfoSection {
					id: providerInfoSection

					imageSource: "qrc:///images/info.svg"
					name: CertificateDescriptionModel.subjectName
					//: LABEL IOS_PHONE ANDROID_PHONE
					title: qsTr("Provider")
				}
				GText {
					id: providerInfoAction

					Accessible.ignored: true

					//: LABEL IOS_PHONE ANDROID_PHONE
					text: qsTr("Touch for more details")
					wrapMode: Text.WordWrap

					anchors {
						left: parent.left
						leftMargin: Style.dimens.small_icon_size + Constants.groupbox_spacing
						right: parent.right
					}
				}
			}
			TintableIcon {
				id: forwardAction

				anchors.right: parent.right
				anchors.verticalCenter: providerEntries.verticalCenter
				source: "qrc:///images/material_arrow_right.svg"
				sourceSize.height: Style.dimens.small_icon_size
				tintColor: Style.color.text
			}
			MouseArea {
				id: mouseArea

				anchors.fill: parent

				onClicked: push(certificateDescriptionPage)
			}
			Component {
				id: certificateDescriptionPage

				CertificateDescriptionPage {
					title: baseItem.title
				}
			}
		}
	}
	GButton {
		Layout.alignment: Qt.AlignHCenter
		icon.source: "qrc:///images/identify.svg"
		//: LABEL IOS_PHONE ANDROID_PHONE %1 can be "CAN" or "PIN"
		text: qsTr("Proceed to %1 entry").arg(NumberModel.isCanAllowedMode ?
			//: LABEL IOS_PHONE Inserted into "Proceed to %1 entry"
			qsTr("CAN") :
			//: LABEL IOS_PHONE Inserted into "Proceed to %1 entry"
			qsTr("PIN"))
		tintIcon: true

		onClicked: rightsAccepted()
	}
	GText {
		id: dataPasswordText

		horizontalAlignment: Text.AlignHCenter
		text: NumberModel.isCanAllowedMode ?
		//: LABEL IOS_PHONE ANDROID_PHONE
		qsTr("By entering the CAN, access to the following data of the ID card will be allowed to the mentioned provider:") :
		//: LABEL IOS_PHONE ANDROID_PHONE
		qsTr("By entering your PIN, access to the following data of your ID card will be allowed to the mentioned provider:")
	}
	GPane {
		Layout.fillWidth: true
		color: Style.color.pane_sublevel
		drawShadow: false
		//: LABEL IOS_PHONE ANDROID_PHONE
		title: qsTr("Transactional information")
		visible: !!workflowModel.transactionInfo || (!writeData.visible && !readData.visible)

		GText {
			activeFocusOnTab: true
			text: workflowModel.transactionInfo
			visible: !!text
			width: parent.width
		}
		GText {
			activeFocusOnTab: true

			//: LABEL IOS_PHONE ANDROID_PHONE
			text: qsTr("The provider mentioned above does not require any data stored on your ID card, only confirmation of you possessing a valid ID card.")
			visible: !writeData.visible && !readData.visible
			width: parent.width
		}
	}
	GPane {
		Layout.fillWidth: true
		color: Style.color.pane_sublevel
		drawShadow: false
		visible: writeData.count > 0

		DataGroup {
			id: writeData

			chat: ChatModel.write

			//: LABEL IOS_PHONE ANDROID_PHONE
			title: qsTr("Write access (update)")
			titleStyle: Style.text.headline
			width: parent.width
			writeAccess: true

			onScrollPageDown: baseItem.scrollPageDown()
			onScrollPageUp: baseItem.scrollPageUp()
		}
	}
	GPane {
		id: readData

		Layout.fillWidth: true
		color: Style.color.pane_sublevel
		drawShadow: false
		visible: requiredData.count > 0 || optionalData.count > 0

		DataGroup {
			id: requiredData

			chat: ChatModel.required

			//: LABEL IOS_PHONE ANDROID_PHONE
			title: qsTr("Read access")
			width: parent.width

			onScrollPageDown: baseItem.scrollPageDown()
			onScrollPageUp: baseItem.scrollPageUp()
		}
		DataGroup {
			id: optionalData

			chat: ChatModel.optional

			//: LABEL IOS_PHONE ANDROID_PHONE
			title: qsTr("Read access (optional)")
			width: parent.width

			onScrollPageDown: baseItem.scrollPageDown()
			onScrollPageUp: baseItem.scrollPageUp()
		}
	}
}
