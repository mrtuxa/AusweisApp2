/**
 * Copyright (c) 2015-2023 Governikus GmbH & Co. KG, Germany
 */
import QtQuick
import Governikus.EnterPasswordView
import Governikus.Global
import Governikus.AuthView
import Governikus.Style
import Governikus.TitleBar
import Governikus.PasswordInfoView
import Governikus.ProgressView
import Governikus.ResultView
import Governikus.View
import Governikus.Workflow
import Governikus.Type.ApplicationModel
import Governikus.Type.ChangePinModel
import Governikus.Type.NumberModel
import Governikus.Type.PasswordType
import Governikus.Type.UiModule
import Governikus.Type.ReaderPlugIn

SectionPage {
	id: baseItem

	property bool autoInsertCard: false
	property bool hidePinTypeSelection: false
	property bool hideTechnologySwitch: false
	property var initialPlugIn: null
	readonly property bool isSmartWorkflow: ChangePinModel.readerPlugInType === ReaderPlugIn.SMART

	signal close
	signal workflowFinished

	contentIsScrolled: !changePinViewContent.atYBeginning
	smartEidUsed: isSmartWorkflow
	title: NumberModel.passwordType === PasswordType.TRANSPORT_PIN ?
	//: LABEL ANDROID IOS
	qsTr("Change Transport PIN") :
	//: LABEL ANDROID IOS
	qsTr("Change PIN")

	navigationAction: NavigationAction {
		action: NavigationAction.Action.Back

		onClicked: baseItem.close()
	}

	Connections {
		function onActivate() {
			changePinViewContent.highlightScrollbar();
		}
	}
	Connections {
		function onFireWorkflowStarted() {
			changePinController.createObject(baseItem);
			setLockedAndHidden(true);
			ChangePinModel.setInitialPluginType();
		}

		enabled: visible
		target: ChangePinModel
	}
	Component {
		id: changePinController

		ChangePinController {
			autoInsertCard: baseItem.autoInsertCard
			hideTechnologySwitch: baseItem.hideTechnologySwitch
			initialPlugIn: baseItem.initialPlugIn
			smartEidUsed: baseItem.smartEidUsed
			stackView: baseItem.stackView
			title: baseItem.title

			onWorkflowFinished: {
				baseItem.workflowFinished();
				this.destroy();
			}
		}
	}
	ChangePinViewContent {
		id: changePinViewContent

		anchors.fill: parent
		moreInformationText: changePinInfo.linkText
		visible: !baseItem.hidePinTypeSelection

		onChangePin: ChangePinModel.startWorkflow(false)
		onChangeTransportPin: ChangePinModel.startWorkflow(true)
		onMoreInformationRequested: push(changePinInfoView)
		onNoPinAvailable: {
			setLockedAndHidden();
			push(pinUnknownView);
		}

		PasswordInfoData {
			id: changePinInfo

			contentType: PasswordInfoContent.Type.CHANGE_PIN
		}
	}
	Component {
		id: changePinInfoView

		PasswordInfoView {
			infoContent: changePinInfo

			navigationAction: NavigationAction {
				action: NavigationAction.Action.Back

				onClicked: pop()
			}

			onAbortCurrentWorkflow: ChangePinModel.cancelWorkflow()
		}
	}
	Component {
		id: pinUnknownView

		PasswordInfoView {
			infoContent: PasswordInfoData {
				contentType: PasswordInfoContent.Type.NO_PIN
			}
			navigationAction: NavigationAction {
				action: NavigationAction.Action.Back

				onClicked: {
					pop();
					setLockedAndHidden(false);
				}
			}
		}
	}
}
