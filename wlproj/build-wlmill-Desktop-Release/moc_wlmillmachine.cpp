/****************************************************************************
** Meta object code from reading C++ file 'wlmillmachine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wlmill/wlmillmachine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlmillmachine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLMillMachine_t {
    QByteArrayData data[128];
    char stringdata0[1345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLMillMachine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLMillMachine_t qt_meta_stringdata_WLMillMachine = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WLMillMachine"
QT_MOC_LITERAL(1, 14, 7), // "saveLog"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "changedEMG"
QT_MOC_LITERAL(4, 34, 10), // "changedRDY"
QT_MOC_LITERAL(5, 45, 13), // "changedSValue"
QT_MOC_LITERAL(6, 59, 9), // "changedSK"
QT_MOC_LITERAL(7, 69, 9), // "changedOn"
QT_MOC_LITERAL(8, 79, 12), // "changedActiv"
QT_MOC_LITERAL(9, 92, 19), // "changedReadyRunList"
QT_MOC_LITERAL(10, 112, 19), // "changedCurrentIndex"
QT_MOC_LITERAL(11, 132, 13), // "changedSpeedF"
QT_MOC_LITERAL(12, 146, 12), // "changedPause"
QT_MOC_LITERAL(13, 159, 19), // "changedHomePosition"
QT_MOC_LITERAL(14, 179, 19), // "changedPercentSpeed"
QT_MOC_LITERAL(15, 199, 18), // "changedPercentSOut"
QT_MOC_LITERAL(16, 218, 14), // "changedCurTool"
QT_MOC_LITERAL(17, 233, 8), // "finished"
QT_MOC_LITERAL(18, 242, 7), // "noActiv"
QT_MOC_LITERAL(19, 250, 5), // "ready"
QT_MOC_LITERAL(20, 256, 13), // "changedMotion"
QT_MOC_LITERAL(21, 270, 11), // "sendMessage"
QT_MOC_LITERAL(22, 282, 4), // "name"
QT_MOC_LITERAL(23, 287, 4), // "data"
QT_MOC_LITERAL(24, 292, 4), // "code"
QT_MOC_LITERAL(25, 297, 5), // "error"
QT_MOC_LITERAL(26, 303, 15), // "changedTrajSize"
QT_MOC_LITERAL(27, 319, 4), // "init"
QT_MOC_LITERAL(28, 324, 17), // "setCompleteScript"
QT_MOC_LITERAL(29, 342, 11), // "setFinished"
QT_MOC_LITERAL(30, 354, 11), // "updateInput"
QT_MOC_LITERAL(31, 366, 12), // "callDataSOut"
QT_MOC_LITERAL(32, 379, 11), // "setDataSOut"
QT_MOC_LITERAL(33, 391, 3), // "per"
QT_MOC_LITERAL(34, 395, 10), // "saveConfig"
QT_MOC_LITERAL(35, 406, 10), // "setMessage"
QT_MOC_LITERAL(36, 417, 5), // "Pause"
QT_MOC_LITERAL(37, 423, 5), // "reset"
QT_MOC_LITERAL(38, 429, 9), // "nameClass"
QT_MOC_LITERAL(39, 439, 5), // "Start"
QT_MOC_LITERAL(40, 445, 4), // "Stop"
QT_MOC_LITERAL(41, 450, 10), // "setCurTool"
QT_MOC_LITERAL(42, 461, 2), // "iT"
QT_MOC_LITERAL(43, 464, 5), // "setOn"
QT_MOC_LITERAL(44, 470, 2), // "on"
QT_MOC_LITERAL(45, 473, 6), // "setOff"
QT_MOC_LITERAL(46, 480, 3), // "off"
QT_MOC_LITERAL(47, 484, 12), // "setAutoStart"
QT_MOC_LITERAL(48, 497, 6), // "enable"
QT_MOC_LITERAL(49, 504, 8), // "getDrive"
QT_MOC_LITERAL(50, 513, 12), // "WLMillDrive*"
QT_MOC_LITERAL(51, 526, 9), // "nameDrive"
QT_MOC_LITERAL(52, 536, 4), // "send"
QT_MOC_LITERAL(53, 541, 19), // "setDriveManualWhell"
QT_MOC_LITERAL(54, 561, 2), // "X1"
QT_MOC_LITERAL(55, 564, 5), // "vmode"
QT_MOC_LITERAL(56, 570, 20), // "setEnableManualWhell"
QT_MOC_LITERAL(57, 591, 13), // "goDriveManual"
QT_MOC_LITERAL(58, 605, 6), // "IncDec"
QT_MOC_LITERAL(59, 612, 4), // "step"
QT_MOC_LITERAL(60, 617, 11), // "goDriveFind"
QT_MOC_LITERAL(61, 629, 12), // "goDriveTeach"
QT_MOC_LITERAL(62, 642, 12), // "goDriveTouch"
QT_MOC_LITERAL(63, 655, 3), // "dir"
QT_MOC_LITERAL(64, 659, 1), // "F"
QT_MOC_LITERAL(65, 661, 12), // "goDriveProbe"
QT_MOC_LITERAL(66, 674, 4), // "type"
QT_MOC_LITERAL(67, 679, 13), // "goDriveHProbe"
QT_MOC_LITERAL(68, 693, 2), // "sd"
QT_MOC_LITERAL(69, 696, 16), // "setPercentManual"
QT_MOC_LITERAL(70, 713, 7), // "isPause"
QT_MOC_LITERAL(71, 721, 2), // "en"
QT_MOC_LITERAL(72, 724, 12), // "setBLNextMov"
QT_MOC_LITERAL(73, 737, 14), // "setContinueMov"
QT_MOC_LITERAL(74, 752, 9), // "setSimpli"
QT_MOC_LITERAL(75, 762, 13), // "setSimpliDist"
QT_MOC_LITERAL(76, 776, 3), // "val"
QT_MOC_LITERAL(77, 780, 9), // "setSmooth"
QT_MOC_LITERAL(78, 790, 13), // "setSmoothDist"
QT_MOC_LITERAL(79, 804, 14), // "setDetPlasmaOn"
QT_MOC_LITERAL(80, 819, 15), // "setPercentSpeed"
QT_MOC_LITERAL(81, 835, 14), // "setPercentSOut"
QT_MOC_LITERAL(82, 850, 17), // "setPercentSpeed50"
QT_MOC_LITERAL(83, 868, 10), // "runLoopPLC"
QT_MOC_LITERAL(84, 879, 24), // "on_changedStatusMPlanner"
QT_MOC_LITERAL(85, 904, 6), // "status"
QT_MOC_LITERAL(86, 911, 10), // "runScriptM"
QT_MOC_LITERAL(87, 922, 2), // "iM"
QT_MOC_LITERAL(88, 925, 11), // "runScriptM3"
QT_MOC_LITERAL(89, 937, 11), // "runScriptM4"
QT_MOC_LITERAL(90, 949, 11), // "runScriptM5"
QT_MOC_LITERAL(91, 961, 11), // "runScriptM7"
QT_MOC_LITERAL(92, 973, 11), // "runScriptM8"
QT_MOC_LITERAL(93, 985, 11), // "runScriptM9"
QT_MOC_LITERAL(94, 997, 12), // "runUserFunc1"
QT_MOC_LITERAL(95, 1010, 12), // "runUserFunc2"
QT_MOC_LITERAL(96, 1023, 12), // "runUserFunc3"
QT_MOC_LITERAL(97, 1036, 12), // "runUserFunc4"
QT_MOC_LITERAL(98, 1049, 12), // "runUserFunc5"
QT_MOC_LITERAL(99, 1062, 8), // "runGCode"
QT_MOC_LITERAL(100, 1071, 4), // "gtxt"
QT_MOC_LITERAL(101, 1076, 18), // "rotAboutRotPointSC"
QT_MOC_LITERAL(102, 1095, 1), // "i"
QT_MOC_LITERAL(103, 1097, 1), // "a"
QT_MOC_LITERAL(104, 1099, 16), // "setCurPositionSC"
QT_MOC_LITERAL(105, 1116, 9), // "nameCoord"
QT_MOC_LITERAL(106, 1126, 3), // "pos"
QT_MOC_LITERAL(107, 1130, 10), // "getInProbe"
QT_MOC_LITERAL(108, 1141, 11), // "getInSDStop"
QT_MOC_LITERAL(109, 1153, 12), // "getInEMGStop"
QT_MOC_LITERAL(110, 1166, 8), // "getInput"
QT_MOC_LITERAL(111, 1175, 5), // "index"
QT_MOC_LITERAL(112, 1181, 9), // "getOutput"
QT_MOC_LITERAL(113, 1191, 9), // "setOutput"
QT_MOC_LITERAL(114, 1201, 3), // "set"
QT_MOC_LITERAL(115, 1205, 14), // "setOutputPulse"
QT_MOC_LITERAL(116, 1220, 4), // "time"
QT_MOC_LITERAL(117, 1225, 12), // "setOutputTog"
QT_MOC_LITERAL(118, 1238, 10), // "getCurTool"
QT_MOC_LITERAL(119, 1249, 7), // "setSOut"
QT_MOC_LITERAL(120, 1257, 1), // "S"
QT_MOC_LITERAL(121, 1259, 10), // "enableSOut"
QT_MOC_LITERAL(122, 1270, 10), // "isTryProbe"
QT_MOC_LITERAL(123, 1281, 16), // "getProbePosition"
QT_MOC_LITERAL(124, 1298, 7), // "isActiv"
QT_MOC_LITERAL(125, 1306, 16), // "getCurPositionSC"
QT_MOC_LITERAL(126, 1323, 8), // "isManual"
QT_MOC_LITERAL(127, 1332, 12) // "isDriveActiv"

    },
    "WLMillMachine\0saveLog\0\0changedEMG\0"
    "changedRDY\0changedSValue\0changedSK\0"
    "changedOn\0changedActiv\0changedReadyRunList\0"
    "changedCurrentIndex\0changedSpeedF\0"
    "changedPause\0changedHomePosition\0"
    "changedPercentSpeed\0changedPercentSOut\0"
    "changedCurTool\0finished\0noActiv\0ready\0"
    "changedMotion\0sendMessage\0name\0data\0"
    "code\0error\0changedTrajSize\0init\0"
    "setCompleteScript\0setFinished\0updateInput\0"
    "callDataSOut\0setDataSOut\0per\0saveConfig\0"
    "setMessage\0Pause\0reset\0nameClass\0Start\0"
    "Stop\0setCurTool\0iT\0setOn\0on\0setOff\0"
    "off\0setAutoStart\0enable\0getDrive\0"
    "WLMillDrive*\0nameDrive\0send\0"
    "setDriveManualWhell\0X1\0vmode\0"
    "setEnableManualWhell\0goDriveManual\0"
    "IncDec\0step\0goDriveFind\0goDriveTeach\0"
    "goDriveTouch\0dir\0F\0goDriveProbe\0type\0"
    "goDriveHProbe\0sd\0setPercentManual\0"
    "isPause\0en\0setBLNextMov\0setContinueMov\0"
    "setSimpli\0setSimpliDist\0val\0setSmooth\0"
    "setSmoothDist\0setDetPlasmaOn\0"
    "setPercentSpeed\0setPercentSOut\0"
    "setPercentSpeed50\0runLoopPLC\0"
    "on_changedStatusMPlanner\0status\0"
    "runScriptM\0iM\0runScriptM3\0runScriptM4\0"
    "runScriptM5\0runScriptM7\0runScriptM8\0"
    "runScriptM9\0runUserFunc1\0runUserFunc2\0"
    "runUserFunc3\0runUserFunc4\0runUserFunc5\0"
    "runGCode\0gtxt\0rotAboutRotPointSC\0i\0a\0"
    "setCurPositionSC\0nameCoord\0pos\0"
    "getInProbe\0getInSDStop\0getInEMGStop\0"
    "getInput\0index\0getOutput\0setOutput\0"
    "set\0setOutputPulse\0time\0setOutputTog\0"
    "getCurTool\0setSOut\0S\0enableSOut\0"
    "isTryProbe\0getProbePosition\0isActiv\0"
    "getCurPositionSC\0isManual\0isDriveActiv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLMillMachine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     100,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      22,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  514,    2, 0x06 /* Public */,
       3,    1,  519,    2, 0x06 /* Public */,
       4,    1,  522,    2, 0x06 /* Public */,
       5,    1,  525,    2, 0x06 /* Public */,
       6,    0,  528,    2, 0x06 /* Public */,
       7,    1,  529,    2, 0x06 /* Public */,
       8,    1,  532,    2, 0x06 /* Public */,
       9,    1,  535,    2, 0x06 /* Public */,
      10,    1,  538,    2, 0x06 /* Public */,
      11,    1,  541,    2, 0x06 /* Public */,
      12,    1,  544,    2, 0x06 /* Public */,
      13,    0,  547,    2, 0x06 /* Public */,
      14,    1,  548,    2, 0x06 /* Public */,
      15,    1,  551,    2, 0x06 /* Public */,
      16,    1,  554,    2, 0x06 /* Public */,
      17,    0,  557,    2, 0x06 /* Public */,
      18,    0,  558,    2, 0x06 /* Public */,
      19,    0,  559,    2, 0x06 /* Public */,
      20,    1,  560,    2, 0x06 /* Public */,
      21,    3,  563,    2, 0x06 /* Public */,
      25,    0,  570,    2, 0x06 /* Public */,
      26,    1,  571,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  574,    2, 0x08 /* Private */,
      28,    1,  575,    2, 0x08 /* Private */,
      29,    0,  578,    2, 0x08 /* Private */,
      30,    0,  579,    2, 0x08 /* Private */,
      31,    0,  580,    2, 0x08 /* Private */,
      32,    1,  581,    2, 0x08 /* Private */,
      34,    0,  584,    2, 0x0a /* Public */,
      35,    3,  585,    2, 0x0a /* Public */,
      36,    0,  592,    2, 0x0a /* Public */,
      37,    0,  593,    2, 0x0a /* Public */,
      38,    0,  594,    2, 0x0a /* Public */,
      39,    0,  595,    2, 0x0a /* Public */,
      40,    0,  596,    2, 0x0a /* Public */,
      41,    1,  597,    2, 0x0a /* Public */,
      43,    1,  600,    2, 0x0a /* Public */,
      45,    1,  603,    2, 0x0a /* Public */,
      47,    1,  606,    2, 0x0a /* Public */,
      49,    2,  609,    2, 0x0a /* Public */,
      49,    1,  614,    2, 0x2a /* Public | MethodCloned */,
      53,    3,  617,    2, 0x0a /* Public */,
      53,    2,  624,    2, 0x2a /* Public | MethodCloned */,
      53,    1,  629,    2, 0x2a /* Public | MethodCloned */,
      56,    1,  632,    2, 0x0a /* Public */,
      56,    0,  635,    2, 0x2a /* Public | MethodCloned */,
      57,    3,  636,    2, 0x0a /* Public */,
      57,    2,  643,    2, 0x2a /* Public | MethodCloned */,
      60,    1,  648,    2, 0x0a /* Public */,
      61,    1,  651,    2, 0x0a /* Public */,
      62,    3,  654,    2, 0x0a /* Public */,
      65,    4,  661,    2, 0x0a /* Public */,
      67,    2,  670,    2, 0x0a /* Public */,
      69,    1,  675,    2, 0x0a /* Public */,
      70,    0,  678,    2, 0x0a /* Public */,
      36,    1,  679,    2, 0x0a /* Public */,
      72,    1,  682,    2, 0x0a /* Public */,
      73,    1,  685,    2, 0x0a /* Public */,
      74,    1,  688,    2, 0x0a /* Public */,
      75,    1,  691,    2, 0x0a /* Public */,
      77,    1,  694,    2, 0x0a /* Public */,
      78,    1,  697,    2, 0x0a /* Public */,
      79,    1,  700,    2, 0x0a /* Public */,
      80,    1,  703,    2, 0x0a /* Public */,
      81,    1,  706,    2, 0x0a /* Public */,
      82,    0,  709,    2, 0x0a /* Public */,
      83,    0,  710,    2, 0x08 /* Private */,
      84,    1,  711,    2, 0x08 /* Private */,
      86,    1,  714,    2, 0x0a /* Public */,
      88,    0,  717,    2, 0x0a /* Public */,
      89,    0,  718,    2, 0x0a /* Public */,
      90,    0,  719,    2, 0x0a /* Public */,
      91,    0,  720,    2, 0x0a /* Public */,
      92,    0,  721,    2, 0x0a /* Public */,
      93,    0,  722,    2, 0x0a /* Public */,
      94,    0,  723,    2, 0x0a /* Public */,
      95,    0,  724,    2, 0x0a /* Public */,
      96,    0,  725,    2, 0x0a /* Public */,
      97,    0,  726,    2, 0x0a /* Public */,
      98,    0,  727,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      99,    1,  728,    2, 0x02 /* Public */,
     101,    2,  731,    2, 0x02 /* Public */,
     104,    2,  736,    2, 0x02 /* Public */,
     107,    0,  741,    2, 0x02 /* Public */,
     108,    0,  742,    2, 0x02 /* Public */,
     109,    0,  743,    2, 0x02 /* Public */,
     110,    1,  744,    2, 0x02 /* Public */,
     112,    1,  747,    2, 0x02 /* Public */,
     113,    2,  750,    2, 0x02 /* Public */,
     115,    3,  755,    2, 0x02 /* Public */,
     117,    1,  762,    2, 0x02 /* Public */,
     118,    0,  765,    2, 0x02 /* Public */,
     119,    1,  766,    2, 0x02 /* Public */,
     121,    1,  769,    2, 0x02 /* Public */,
     122,    1,  772,    2, 0x02 /* Public */,
     123,    2,  775,    2, 0x02 /* Public */,
     124,    0,  780,    2, 0x02 /* Public */,
     125,    1,  781,    2, 0x02 /* Public */,
     126,    0,  784,    2, 0x02 /* Public */,
     127,    1,  785,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Long,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   22,   23,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   33,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   22,   23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void, QMetaType::Bool,   44,
    QMetaType::Void, QMetaType::Bool,   46,
    QMetaType::Void, QMetaType::Bool,   48,
    0x80000000 | 50, QMetaType::QString, QMetaType::Bool,   51,   52,
    0x80000000 | 50, QMetaType::QString,   51,
    QMetaType::Void, QMetaType::QString, QMetaType::UChar, QMetaType::Bool,   22,   54,   55,
    QMetaType::Void, QMetaType::QString, QMetaType::UChar,   22,   54,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Float,   22,   58,   59,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   22,   58,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   51,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Float,   51,   63,   64,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Float, QMetaType::Int,   51,   63,   64,   66,
    QMetaType::Void, QMetaType::Float, QMetaType::Bool,   64,   68,
    QMetaType::Void, QMetaType::Float,   33,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   71,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Double,   76,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Void, QMetaType::Double,   76,
    QMetaType::Void, QMetaType::Bool,   44,
    QMetaType::Void, QMetaType::Double,   33,
    QMetaType::Void, QMetaType::Double,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   85,
    QMetaType::Void, QMetaType::Int,   87,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString,  100,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  102,  103,
    QMetaType::Void, QMetaType::QString, QMetaType::Double,  105,  106,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int,  111,
    QMetaType::Bool, QMetaType::Int,  111,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,  111,  114,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Int,  111,  114,  116,
    QMetaType::Void, QMetaType::Int,  111,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Float,  120,
    QMetaType::Void, QMetaType::Bool,   48,
    QMetaType::Bool, QMetaType::Bool,   63,
    QMetaType::Double, QMetaType::QString, QMetaType::Bool,   51,   63,
    QMetaType::Bool,
    QMetaType::Double, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,

       0        // eod
};

void WLMillMachine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLMillMachine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->changedEMG((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->changedRDY((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->changedSValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changedSK(); break;
        case 5: _t->changedOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->changedActiv((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->changedReadyRunList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->changedCurrentIndex((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 9: _t->changedSpeedF((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->changedPause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->changedHomePosition(); break;
        case 12: _t->changedPercentSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->changedPercentSOut((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->changedCurTool((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->finished(); break;
        case 16: _t->noActiv(); break;
        case 17: _t->ready(); break;
        case 18: _t->changedMotion((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 20: _t->error(); break;
        case 21: _t->changedTrajSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->init(); break;
        case 23: _t->setCompleteScript((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->setFinished(); break;
        case 25: _t->updateInput(); break;
        case 26: _t->callDataSOut(); break;
        case 27: _t->setDataSOut((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 28: _t->saveConfig(); break;
        case 29: _t->setMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 30: _t->Pause(); break;
        case 31: _t->reset(); break;
        case 32: { QString _r = _t->nameClass();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->Start(); break;
        case 34: _t->Stop(); break;
        case 35: _t->setCurTool((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->setOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->setOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->setAutoStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: { WLMillDrive* _r = _t->getDrive((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< WLMillDrive**>(_a[0]) = std::move(_r); }  break;
        case 40: { WLMillDrive* _r = _t->getDrive((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< WLMillDrive**>(_a[0]) = std::move(_r); }  break;
        case 41: _t->setDriveManualWhell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 42: _t->setDriveManualWhell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 43: _t->setDriveManualWhell((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 44: _t->setEnableManualWhell((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->setEnableManualWhell(); break;
        case 46: _t->goDriveManual((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 47: _t->goDriveManual((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->goDriveFind((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 49: _t->goDriveTeach((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 50: _t->goDriveTouch((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 51: _t->goDriveProbe((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 52: _t->goDriveHProbe((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 53: _t->setPercentManual((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 54: { bool _r = _t->isPause();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 55: _t->Pause((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->setBLNextMov((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->setContinueMov((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->setSimpli((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->setSimpliDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 60: _t->setSmooth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->setSmoothDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 62: _t->setDetPlasmaOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->setPercentSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 64: _t->setPercentSOut((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 65: _t->setPercentSpeed50(); break;
        case 66: _t->runLoopPLC(); break;
        case 67: _t->on_changedStatusMPlanner((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 68: _t->runScriptM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 69: _t->runScriptM3(); break;
        case 70: _t->runScriptM4(); break;
        case 71: _t->runScriptM5(); break;
        case 72: _t->runScriptM7(); break;
        case 73: _t->runScriptM8(); break;
        case 74: _t->runScriptM9(); break;
        case 75: _t->runUserFunc1(); break;
        case 76: _t->runUserFunc2(); break;
        case 77: _t->runUserFunc3(); break;
        case 78: _t->runUserFunc4(); break;
        case 79: _t->runUserFunc5(); break;
        case 80: { bool _r = _t->runGCode((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 81: _t->rotAboutRotPointSC((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 82: _t->setCurPositionSC((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 83: { bool _r = _t->getInProbe();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 84: { bool _r = _t->getInSDStop();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 85: { bool _r = _t->getInEMGStop();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 86: { bool _r = _t->getInput((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 87: { bool _r = _t->getOutput((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 88: _t->setOutput((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 89: _t->setOutputPulse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 90: _t->setOutputTog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 91: { int _r = _t->getCurTool();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 92: _t->setSOut((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 93: _t->enableSOut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 94: { bool _r = _t->isTryProbe((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 95: { double _r = _t->getProbePosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 96: { bool _r = _t->isActiv();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 97: { double _r = _t->getCurPositionSC((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 98: { bool _r = _t->isManual();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 99: { bool _r = _t->isDriveActiv((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLMillMachine::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::saveLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedEMG)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedRDY)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedSValue)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedSK)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedOn)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedActiv)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedReadyRunList)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedCurrentIndex)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedSpeedF)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedPause)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedHomePosition)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedPercentSpeed)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedPercentSOut)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedCurTool)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::finished)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::noActiv)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::ready)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedMotion)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::sendMessage)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::error)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (WLMillMachine::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLMillMachine::changedTrajSize)) {
                *result = 21;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLMillMachine::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_WLMillMachine.data,
    qt_meta_data_WLMillMachine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLMillMachine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLMillMachine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLMillMachine.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int WLMillMachine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 100)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 100;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 100)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 100;
    }
    return _id;
}

// SIGNAL 0
void WLMillMachine::saveLog(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLMillMachine::changedEMG(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLMillMachine::changedRDY(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLMillMachine::changedSValue(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLMillMachine::changedSK()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WLMillMachine::changedOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WLMillMachine::changedActiv(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WLMillMachine::changedReadyRunList(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WLMillMachine::changedCurrentIndex(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WLMillMachine::changedSpeedF(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void WLMillMachine::changedPause(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void WLMillMachine::changedHomePosition()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void WLMillMachine::changedPercentSpeed(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void WLMillMachine::changedPercentSOut(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void WLMillMachine::changedCurTool(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void WLMillMachine::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void WLMillMachine::noActiv()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void WLMillMachine::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void WLMillMachine::changedMotion(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void WLMillMachine::sendMessage(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void WLMillMachine::error()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void WLMillMachine::changedTrajSize(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
