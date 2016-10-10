#include "tablecontainerview.h"

#include <QDebug>
TableContainerView::TableContainerView(QWidget *parent) : QTableWidget(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTableWidget::customContextMenuRequested,
            this, &TableContainerView::showContextMenu);
}

TableContainerView::~TableContainerView()
{
}

void TableContainerView::showContextMenu(const QPoint &point)
{
    auto ids = getSelectedIds();
    QMenu contextMenu(tr("Context menu"), this);

    QAction actionAdd("add", this);
    contextMenu.addAction(&actionAdd);
    connect(&actionAdd, &QAction::triggered, this, [=](){
        emit openEditor(-1);
    });

    QAction actionPatch("patch", this);
    if (ids.size() == 1) {
        contextMenu.addAction(&actionPatch);
        connect(&actionPatch, &QAction::triggered, this, [ids, this](){
            emit openEditor(ids.at(0));
        });
    }

    QAction actionRemove("remove", this);
    if (!ids.isEmpty()) {
        contextMenu.addAction(&actionRemove);
        connect(&actionRemove, &QAction::triggered, this, [ids, this](){
            foreach (int id, ids )
                emit removeObject(id);
        });
    }
    contextMenu.exec(mapToGlobal(point));
}


void TableContainerView::onGotObjects(QList<BaseDTO *> listObjects)
{
    foreach (auto object, listObjects)
        onAddObject(*object);
}

void TableContainerView::onAddObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnAddObject(object);
    setSortingEnabled(isSorted);
}

void TableContainerView::onPatchObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnPatchObject(object);
    setSortingEnabled(isSorted);
}

void TableContainerView::onRemoveObject(const BaseDTO &object)
{
    setSortingEnabled(false);
    privateOnRemoveObject(object);
    setSortingEnabled(isSorted);
}

