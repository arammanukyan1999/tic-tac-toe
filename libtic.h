#ifndef LIBTIC
#define LIBTIC
#include <QProxyStyle>

namespace Tic {
    enum XOStates { X,O,Empty };

    class Style_tweaks : public QProxyStyle {
        public:

            void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                               QPainter *painter, const QWidget *widget) const
            {
                /* do not draw focus rectangles - this permits modern styling */
                if (element == QStyle::PE_FrameFocusRect)
                    return;

                QProxyStyle::drawPrimitive(element, option, painter, widget);
            }
    };

    struct GameData {
        QString XPalyerName;
        QString OPlayerName;
        int width;
        int height;
        int winSize;
        XOStates compPlayer;
        short players;
    };
}


#endif // LIBTIC

