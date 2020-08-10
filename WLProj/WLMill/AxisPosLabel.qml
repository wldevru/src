import QtQuick 2.5
import QtQuick.Window 2.0
//import QtQuick.Controls 2.0
//import QtQuick.Studio.Components 1.0


Rectangle{
    id: root
    implicitHeight: 40
    implicitWidth: 200
    radius: 5
    color: "transparent"

    signal qmlSignalClick(int val)

    property string p_data :   "1234.56"
    property string p_data53:  "1234.56"
    property string p_name:    "X:"
    property color  p_color:   "green"
    property color  p_scolor:  "green"
    property string p_feed:    "F:9999"


    Rectangle{
        id: rectName
        color: "silver"
        height: root.height
        width:  nameCoor.width+4

        radius: 5

        anchors.left:  root.left
        anchors.verticalCenter: root.verticalCenter
        anchors.right: nameCoor.right

    Text {
        id: nameCoor
        color: root.p_color
        text: (root.p_name)
        //font.bold: true
        font.pixelSize: root.height*0.8
        anchors.centerIn: rectName

        }

    MouseArea{
        anchors.fill: rectName

        hoverEnabled :true
/*
        onExited:{
            nameCoor.color=root.p_color
        }

        onEntered:{
            nameCoor.color=root.p_scolor
        }
*/
        onClicked: {
             root.qmlSignalClick(3);
        }
    }
    }

    Text {
        id: data
        z:1
        color: root.p_color
        text: (root.p_data)
        //font.bold: true
        font.pixelSize: root.height*0.8

        anchors.left:  rectName.right
        anchors.leftMargin: 5
        anchors.verticalCenter: root.verticalCenter
      //  style: Text.Outline
       // styleColor: "black"
        MouseArea{
            anchors.fill: parent
/*
            hoverEnabled :true

            onExited:{
                data.color=root.p_color
            }

            onEntered:{
                data.color=root.p_scolor
            }
*/
            onClicked: {
                 root.qmlSignalClick(0);
            }

        }
    }

    Text {
        id: data53
        //width: font.pixelSize*5
        color: "brown"
        text:  root.p_data53
        font.pixelSize: root.height*0.4
        anchors.right:  parent.right
        anchors.rightMargin: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2

      /*  ToolTip
        {
        text: "Machine coord (G53)"
        }*/

        MouseArea{
            anchors.fill: parent
/*

            hoverEnabled :true

            onExited:{
                data53.color="brown"
            }

            onEntered:{
                data53.color=root.p_scolor
            }
*/
            onClicked: {
                root.qmlSignalClick(1);
            }

        }
    }

    Text {
        id: feed
        color: "blue"
        text: root.p_feed
        font.pixelSize: root.height*0.4
        anchors.right: parent.right
        anchors.top:   parent.top
        anchors.margins: 2

     /*   ToolTip
        {
        text: "Feed axis (uint/min)"
        }*/
    }




    ///parent.color="white"



}
