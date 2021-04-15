import QtQuick 2.15

Item {
    anchors.fill: parent

    Rectangle {
        id: rectangle
        opacity: 0.5
        color: "#000000"
        anchors.fill: parent

        Image {
            id: animatedImage
            width: 100
            height: 100
            anchors.verticalCenter: parent.verticalCenter
            source: "icons/Rolling-1s-200px.svg"
            anchors.horizontalCenter: parent.horizontalCenter

            RotationAnimator {
                target: animatedImage;
                from: 0;
                to: 360;
                duration: 1000
                loops: Animation.Infinite
                running: true
            }
        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}
}
##^##*/
