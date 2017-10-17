// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <ProxyModels/DeepFilterProxyModel.h>

namespace ACE
{
class IAudioSystemEditor;
class IAudioSystemItem;

namespace AudioModelUtils
{
	void DecodeImplMimeData(const QMimeData* pData, std::vector<IAudioSystemItem*>& outItems);
} // namespace AudioModelUtils

class CMiddlewareDataModel final : public QAbstractItemModel
{
public:

	enum class EMiddlewareDataColumns
	{
		Name,
		Count,
	};

	// TODO: Should be replaced with the new attribute system
	enum class EMiddlewareDataAttributes
	{
		Type = Qt::UserRole + 1,
		Connected,
		Placeholder,
		Localized,
		Id,
	};

	CMiddlewareDataModel();

	// QAbstractItemModel
	virtual int             rowCount(QModelIndex const& parent) const override;
	virtual int             columnCount(QModelIndex const& parent) const override;
	virtual QVariant        data(QModelIndex const& index, int role) const override;
	virtual QVariant        headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	virtual Qt::ItemFlags   flags(QModelIndex const& index) const override;
	virtual QModelIndex     index(int row, int column, QModelIndex const& parent = QModelIndex()) const override;
	virtual QModelIndex     parent(QModelIndex const& index) const override;
	virtual Qt::DropActions supportedDragActions() const override;
	virtual QStringList     mimeTypes() const override;
	virtual QMimeData*      mimeData(QModelIndexList const& indexes) const override;
	// ~QAbstractItemModel

	IAudioSystemItem* ItemFromIndex(QModelIndex const& index) const;
	QModelIndex       IndexFromItem(IAudioSystemItem const* const pItem) const;
	void              Reset();

	static char const* const ms_szMimeType;

private:

	IAudioSystemEditor* m_pAudioSystem;
};

class CMiddlewareDataFilterProxyModel final : public QDeepFilterProxyModel
{
public:

	CMiddlewareDataFilterProxyModel(QObject* parent);

	// QSortFilterProxyModel
	virtual bool lessThan(QModelIndex const& left, QModelIndex const& right) const override;
	// ~QSortFilterProxyModel

	// QDeepFilterProxyModel
	virtual bool rowMatchesFilter(int source_row, QModelIndex const& source_parent) const override;
	// ~QDeepFilterProxyModel

	void SetHideConnected(bool const hideConnected);
	
private:

	bool m_hideConnected;
};
} // namespace ACE