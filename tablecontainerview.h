#ifndef TABLECONTAINERVIEW_H
#define TABLECONTAINERVIEW_H

#include <QVBoxLayout>
#include <QTableWidget>
#include <QAction>
#include <QWidgetAction>
#include <QMenu>
#include <QHeaderView>


class BaseDTO;

class TableContainerView : public QTableWidget
{
    Q_OBJECT
public:
    TableContainerView(QWidget* parent = nullptr);
    virtual ~TableContainerView();

    virtual QList<int> getSelectedIds() = 0;

    void onAddObject(const BaseDTO &object);
    void onPatchObject(const BaseDTO &object);
    void onRemoveObject(const BaseDTO &object);

    void deleteSelectedObjects();

private:
    virtual void privateOnAddObject(const BaseDTO &object) = 0;
    virtual void privateOnPatchObject(const BaseDTO &object ) = 0;
    virtual void privateOnRemoveObject(const BaseDTO &object ) = 0;

    QWidgetAction * createActionWidget(const QString &name, const QString &objName);

    QMenu *menu;

private slots:
    void showContextMenu(const QPoint &point);

signals:
    void openEditor(int id);
    void removeObject(int id);
    void removeObjects(const QList<int> ids);

protected:
    bool isSorted;
    virtual void initView() = 0;

    virtual QString getUnitDescription(int id) = 0;

    virtual bool askToDelete(bool single, QList<int> ids) = 0;

    QString msgOnDeleteOne;
    QString msgOnDeleteMore;

    QString containedUnit;
    QString containedUnits;
};

#endif // TABLECONTAINERVIEW_H
