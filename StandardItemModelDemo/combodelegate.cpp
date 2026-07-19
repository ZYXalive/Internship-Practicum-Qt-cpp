#include "combodelegate.h"

#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>

ComboDelegate::ComboDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    Q_UNUSED(option);

    // 第0列（账号）使用行编辑
    if (index.column() == 0) {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(10000, 99999, editor));
        return editor;
    }
    // 第1列（用户）使用行编辑
    else if (index.column() == 1) {
        QLineEdit *editor = new QLineEdit(parent);
        return editor;
    }
    // 第2列（年龄）使用下拉框选择年龄段
    else if (index.column() == 2) {
        QComboBox *editor = new QComboBox(parent);
        editor->setEditable(true);
        editor->addItems({
            "18", "19", "20", "21", "22", "23", "24", "25",
            "26", "27", "28", "29", "30", "31", "32"
        });
        return editor;
    }

    return nullptr;
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 1) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit)
            lineEdit->setText(index.data(Qt::DisplayRole).toString());
    } else if (index.column() == 2) {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            QString currentText = index.data(Qt::DisplayRole).toString();
            int idx = comboBox->findText(currentText);
            if (idx >= 0)
                comboBox->setCurrentIndex(idx);
            else
                comboBox->setEditText(currentText);
        }
    }
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 1) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit)
            model->setData(index, lineEdit->text());
    } else if (index.column() == 2) {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox)
            model->setData(index, comboBox->currentText());
    }
}

void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
