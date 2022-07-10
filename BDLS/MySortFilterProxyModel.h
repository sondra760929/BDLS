#pragma once

#include <QSortFilterProxyModel>
#include <QDate>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
    MySortFilterProxyModel(QObject *parent);
	~MySortFilterProxyModel();

    void updateFilter(int index, QString value);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(QDate date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(QDate date);

    QMap<int, QRegularExpression> mapFilters;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool IsEditable = true;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
    bool dateInRange(QDate date) const;

    QDate minDate;
    QDate maxDate;
};
