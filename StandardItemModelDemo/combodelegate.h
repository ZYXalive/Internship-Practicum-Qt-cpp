#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QStyledItemDelegate>

class ComboDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ComboDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif
