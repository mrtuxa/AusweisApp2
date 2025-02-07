/**
 * Copyright (c) 2022-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick
import QtQuick.Controls
import Governikus.Type.ApplicationModel
import Governikus.Global
import Governikus.Style

Column {
	spacing: Constants.text_spacing

	GText {
		horizontalAlignment: Text.AlignHCenter
		//: INFO IOS Let user know to check the application settings for local network permission
		text: qsTr("Ensure that access to the local network is allowed in your settings.")
		width: parent.width
	}
	MoreInformationLink {
		anchors.horizontalCenter: parent.horizontalCenter
		iconVisible: false
		//: INFO IOS Link to application settings
		text: qsTr("Go to application settings")

		onClicked: ApplicationModel.showSettings(ApplicationModel.SETTING_APP)
	}
}
