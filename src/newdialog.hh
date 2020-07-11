/* newdialgo.hh
 * contains the class declarations
 * this has to be in a header file for QT to function */

#ifndef ND_HH
#define ND_HH

#include <QGraphicsScene>
#include <QGraphicsView>

#include "ui_newmap.h"

class NewDialog : public QDialog
{
    Q_OBJECT

private:
    QComboBox* combo;
    bool success;
    int option;
    bool regular;

public:
    NewDialog();
    void setup_triggers(Ui_NewMapDialog* nd);
    int get_selection();
    bool is_regular();

public slots:
    void nd_ok();
    void nd_cancel();
    void on_regular();
    void on_affine();
};

#endif
