import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "app_activity_indicator.js" as AppActivityIndicator

SwipeView{
    id: swipeLogin

    Connections {
        target: Auth
        function onSignInFailed(error) {
            textError.text = error
            AppActivityIndicator.destroyAppActivityIndicator()
        }

        function onCreateAccountFailed(error){
            textErrorRegistration.text = error
            AppActivityIndicator.destroyAppActivityIndicator()
        }

        function onAccountCreated(){
            swipeLogin.setCurrentIndex(0)
            emailSignIn.text = emailRegistration.text
            passwordSignIn.text = passwordRegistration.text
            AppActivityIndicator.destroyAppActivityIndicator()
        }

        function onSignInSuccessed(){
            AppActivityIndicator.destroyAppActivityIndicator()
        }
    }

    Item {
        id: elementSignIn

        Rectangle {
            id: backgroundSignIn
            color: "#222222"
            anchors.fill: parent

            LoginTextInput{
                id: emailSignIn
                width: 300
                height: 30
                x: 214
                y: 118
                anchors.horizontalCenter: parent.horizontalCenter
                hidenText: qsTr("Enter mail")
            }

            LoginTextInput {
                id: passwordSignIn
                x: 214
                y: 174
                width: 300
                height: 30
                hidenText: qsTr("Enter password")
                echoMode: TextInput.Password
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Switch {
                id: login_rememberSignIn
                width: 300
                height: 30
                text: qsTr("Remember me")
                anchors.left: passwordSignIn.left
                anchors.top: passwordSignIn.bottom
                anchors.leftMargin: 0
                anchors.topMargin: 28
                font.pixelSize: 30

                palette {
                    dark: "#18A0FB"
                    windowText: "white"
                }

            }

            Button {
                id: button_sign_inSignIn
                x: 370
                text: qsTr("Sign In")
                anchors.right: login_rememberSignIn.right
                anchors.top: login_rememberSignIn.bottom
                anchors.rightMargin: 0
                anchors.topMargin: 25

                onClicked: {
                    var emailPat = /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/
                    textError.text = ""
                    var errorCount = 0

                    if(emailSignIn.text.length == 0){
                        errorCount++
                        textError.text += qsTr("Error: Email is empty")
                    }

                    if(passwordSignIn.text.length == 0){
                        if(errorCount > 0){
                            textError.text += "\n"
                        }

                        textError.text += qsTr("Error: Password is empty")
                        errorCount++
                    }

                    if(!emailPat.test(emailSignIn.text)){
                        if(errorCount > 0){
                            textError.text += "\n"
                        }
                        textError.text += qsTr("Error: Incorect email")
                        errorCount++
                    }

                    if(errorCount === 0){
                        Auth.email = emailSignIn.text
                        Auth.password = passwordSignIn.text
                        Auth.signIn()
                        AppActivityIndicator.createAppActivityIndicator(swipeLogin.parent)
                    }
                }

            }

            Text{
                id: textError
                width: textError.implicitWidth
                height: 30
                color: "red"
                anchors.top: button_sign_inSignIn.bottom
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 25


            }

            Text {
                id: titleSignIn
                x: 268
                y: 50
                width: 104
                height: 49
                color: "#eeebeb"
                text: qsTr("Login")
                anchors.bottom: emailSignIn.top
                font.pixelSize: 38
                anchors.bottomMargin: 19
                anchors.horizontalCenter: emailSignIn.horizontalCenter
                font.bold: true
            }

            Text {
                id: create_accountSignIn
                width: create_accountSignIn.implicitWidth
                height: 30
                color: "#bebdbd"
                text: qsTr("Create Account")
                anchors.left: login_rememberSignIn.left
                anchors.top: login_rememberSignIn.bottom
                font.pixelSize: 20
                styleColor: "#e9e7e7"
                anchors.leftMargin: 0
                anchors.topMargin: 30

                MouseArea{
                    anchors.fill: create_accountSignIn
                    hoverEnabled: true
                    onEntered: {
                        create_accountSignIn.color = "#18A0FB"
                        create_accountSignIn.font.underline = true
                    }

                    onExited: {
                        create_accountSignIn.color = "#e9e7e7"
                        create_accountSignIn.font.underline = false
                    }

                    onClicked: {
                        swipeLogin.setCurrentIndex(1)
                    }
                }
            }
        }
    }

    Item {
        id: elementRegistration
        Rectangle {
            id: backgroundRegistration
            color: "#222222"
            anchors.fill: parent

            Rectangle{
                id: back
                anchors.top: parent.top
                anchors.left: parent.left
                width: 50
                height: 50
                color: "#222222"
                Image {
                    id: backImage
                    anchors.fill: parent
                    anchors.margins: 2
                    sourceSize{
                        width: parent.height
                        height: parent.height
                    }
                    antialiasing: true
                    source: "qrc:/icons/arrow-pointing-to-right.svg"
                    visible: false
                }

                ColorOverlay {
                    id: backImageOverlay
                    anchors.fill: backImage
                    anchors.margins: 2
                    source: backImage
                    color: "lightGrey"
                    antialiasing: true
                    transformOrigin: Item.Center
                    rotation: 180
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        backImageOverlay.color = "white"
                    }

                    onExited: {
                        backImageOverlay.color = "lightGrey"
                    }

                    onClicked: {
                        swipeLogin.setCurrentIndex(0)
                    }
                }
            }
            LoginTextInput{
                id: emailRegistration
                width: 300
                height: 30
                x: 214
                y: 118
                anchors.horizontalCenter: parent.horizontalCenter
                hidenText: qsTr("Enter mail")
            }

            LoginTextInput {
                id: passwordRegistration
                x: 214
                y: 174
                width: 300
                height: 30
                hidenText: qsTr("Enter password")
                echoMode: TextInput.Password
                anchors.top: emailRegistration.bottom
                anchors.left: emailRegistration.left
                anchors.topMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter
            }

            LoginTextInput {
                id: passwordRepeatRegistration
                width: 300
                height: 30
                hidenText: qsTr("Repeat password")
                echoMode: TextInput.Password
                anchors.top: passwordRegistration.bottom
                anchors.left: passwordRegistration.left
                anchors.topMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Button {
                id: button_CreateAccountRegistration
                text: qsTr("Create Account")
                anchors.top: passwordRepeatRegistration.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 25

                onClicked: {
                    var emailPat = /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/
                    textErrorRegistration.text = ""
                    var errorCount = 0

                    if(emailRegistration.text.length == 0){
                        errorCount++
                        textErrorRegistration.text += qsTr("Error: Email is empty")
                    }

                    if(passwordRegistration.text.length == 0 || passwordRepeatRegistration.text.length == 0){
                        if(errorCount > 0){
                            textErrorRegistration.text += "\n"
                        }

                        textErrorRegistration.text += qsTr("Error: Password is empty")
                        errorCount++
                    }

                    if(!emailPat.test(emailRegistration.text)){
                        if(errorCount > 0){
                            textErrorRegistration.text += "\n"
                        }
                        textErrorRegistration.text += qsTr("Error: Incorect email")
                        errorCount++
                    }

                    if(passwordRegistration.text !== passwordRepeatRegistration.text){
                        if(errorCount > 0){
                            textErrorRegistration.text += "\n"
                        }
                        textErrorRegistration.text += qsTr("Error: Passwords are not identical")
                        errorCount++
                    }

                    if(errorCount === 0){
                        Auth.email = emailRegistration.text
                        Auth.password = passwordRegistration.text
                        Auth.createAccount()
                        AppActivityIndicator.createAppActivityIndicator(swipeLogin.parent)
                    }
                }

            }

            Text{
                id: textErrorRegistration
                width: textErrorRegistration.implicitWidth
                height: 30
                color: "red"
                anchors.top: button_CreateAccountRegistration.bottom
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 25


            }

            Text {
                id: titleRegistration
                x: 268
                y: 50
                width: titleRegistration.implicitWidth
                height: 49
                color: "#eeebeb"
                text: qsTr("Create Account")
                anchors.bottom: emailRegistration.top
                font.pixelSize: 38
                anchors.bottomMargin: 19
                anchors.horizontalCenter: emailRegistration.horizontalCenter
                font.bold: true
            }
        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}D{i:4}D{i:5}D{i:7}D{i:1}
}
##^##*/
