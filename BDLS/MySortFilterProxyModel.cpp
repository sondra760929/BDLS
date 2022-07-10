#include "MySortFilterProxyModel.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
	: QSortFilterProxyModel(parent)
{
}

MySortFilterProxyModel::~MySortFilterProxyModel()
{
}

void MySortFilterProxyModel::updateFilter(int index, QString value)
{
    mapFilters[index] = QRegularExpression(value);
    invalidateFilter();
}

bool MySortFilterProxyModel::lessThan(const QModelIndex& left,
    const QModelIndex& right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
 
    if (leftData.userType() == QMetaType::Int) {
        return leftData.toInt() < rightData.toInt();
    }
    else {
        static const QRegularExpression emailPattern("[\\w\\.]*@[\\w\\.]*");

        QString leftString = leftData.toString();
        if (left.column() == 1) {
            const QRegularExpressionMatch match = emailPattern.match(leftString);
            if (match.hasMatch())
                leftString = match.captured(0);
        }
        QString rightString = rightData.toString();
        if (right.column() == 1) {
            const QRegularExpressionMatch match = emailPattern.match(rightString);
            if (match.hasMatch())
                rightString = match.captured(0);
        }

        return QString::localeAwareCompare(leftString, rightString) < 0;
    }
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow,
    const QModelIndex& sourceParent) const
{
    bool is_ok = true;;
    QList<int> keys = mapFilters.keys();
    for (int i = 0; i < keys.count(); i++)
    {
        int index = keys[i];
        if (mapFilters[index].isValid())
        {
            QModelIndex index0 = sourceModel()->index(sourceRow, index, sourceParent);
            QString value_string = sourceModel()->data(index0).toString();
            QString pattern = mapFilters[index].pattern();
            QRegularExpressionMatch match = mapFilters[index].match(value_string);
            bool row_ok = match.hasMatch();
            //bool row_ok = value_string.contains(mapFilters[index]);

            is_ok = is_ok && row_ok;
        }
    }
    return is_ok;
    //QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    //QModelIndex index1 = sourceModel()->index(sourceRow, 1, sourceParent);
    //QModelIndex index2 = sourceModel()->index(sourceRow, 2, sourceParent);

    //return (sourceModel()->data(index0).toString().contains(filterRegularExpression())
    //    || sourceModel()->data(index1).toString().contains(filterRegularExpression()))
    //    && dateInRange(sourceModel()->data(index2).toDate());
}

bool MySortFilterProxyModel::dateInRange(QDate date) const
{
    return (!minDate.isValid() || date > minDate)
        && (!maxDate.isValid() || date < maxDate);
}

void MySortFilterProxyModel::setFilterMinimumDate(QDate date)
{
    minDate = date;
    invalidateFilter();
}

void MySortFilterProxyModel::setFilterMaximumDate(QDate date)
{
    maxDate = date;
    invalidateFilter();
}
Qt::ItemFlags MySortFilterProxyModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.column() == 0 || IsEditable == false)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}
