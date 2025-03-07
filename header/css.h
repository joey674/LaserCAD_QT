#ifndef CSS_H
#define CSS_H

#include <QString>

QString buttonStyle1 = R"(
        QToolButton {
            border-radius: 15px;
            background-color: #d0d0d0;
            color: black;
            padding: 5px;
            margin: 0px;
        }
        QToolButton:hover {
            background-color: #c0c0c0;
        }
        QToolButton:pressed {
            background-color: #b0b0b0;
        }
        QToolButton:checked {
            background-color: #b0b0b0;
        }
    )";

QString buttonStyle2 = R"(
        QPushButton{
            background-color: skyblue;
            border: none;
            border-radius: 12px;
            color:white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            cursor: pointer;
            transition-duration: 0.4s;
        }
        QPushButton:hover{
            box-shadow: 0 12px 16px 0 rgba(0,0,0,.24),
            0 17px 50px 0 rgba(0,0,0,.19);
        }
    )";


#endif // CSS_H
