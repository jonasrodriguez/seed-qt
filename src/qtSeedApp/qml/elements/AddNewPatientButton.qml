import QtQuick 2.0
import QtQuick.Shapes 1.0

Shape {
    id: canvas
    height: parent.height * 0.8
    width: height
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    ShapePath {
        strokeColor: "white"
        strokeWidth: 3
        startX: canvas.width * 0.2
        startY: (canvas.height / 2)
        PathLine {x:canvas.width / 2    ; y:canvas.height / 2}
        PathLine {x:canvas.width / 2    ; y:canvas.height * 0.2}
        PathLine {x:canvas.width / 2    ; y:canvas.height * 0.8}
        PathLine {x:canvas.width / 2    ; y:canvas.height / 2}
        PathLine {x:canvas.width * 0.8  ; y:canvas.height / 2}
    }
}
