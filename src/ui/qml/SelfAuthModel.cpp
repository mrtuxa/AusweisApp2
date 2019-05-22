/*!
 * \copyright Copyright (c) 2015-2019 Governikus GmbH & Co. KG, Germany
 */

#include "SelfAuthModel.h"

#include "context/SelfAuthContext.h"
#include "LanguageLoader.h"

using namespace governikus;


void SelfAuthModel::onSelfAuthenticationDataChanged()
{
	beginResetModel();
	mSelfData.clear();

	if (mContext && mContext->getSelfAuthenticationData().isValid())
	{
		const auto& selfdata = mContext->getSelfAuthenticationData().getOrderedSelfData();
		for (const auto& entry : selfdata)
		{
			if (entry.first.isEmpty())
			{
				Q_ASSERT(!mSelfData.isEmpty());
				const auto& previous = mSelfData.takeLast();
				mSelfData << qMakePair(previous.first, previous.second + QStringLiteral("<br/>") + entry.second);
			}
			else
			{
				mSelfData << entry;
			}
		}
	}

	endResetModel();
}


SelfAuthModel::SelfAuthModel(QObject* pParent)
	: QAbstractListModel(pParent)
	, mContext()
	, mSelfData()
{
	onSelfAuthenticationDataChanged();
}


void SelfAuthModel::resetContext(const QSharedPointer<SelfAuthContext>& pContext)
{
	mContext = pContext;
	if (mContext)
	{
		connect(mContext.data(), &SelfAuthContext::fireSelfAuthenticationDataChanged, this, &SelfAuthModel::onSelfAuthenticationDataChanged);
	}
	onSelfAuthenticationDataChanged();
}


void SelfAuthModel::startWorkflow()
{
	Q_EMIT fireStartWorkflow();
}


void SelfAuthModel::cancelWorkflow()
{
	if (mContext)
	{
		Q_EMIT mContext->fireCancelWorkflow();
	}
}


bool SelfAuthModel::isBasicReader()
{
	if (mContext)
	{
		return mContext->getCardConnection()->getReaderInfo().isBasicReader();
	}

	return true;
}


int SelfAuthModel::rowCount(const QModelIndex&) const
{
	return mSelfData.size();
}


QVariant SelfAuthModel::data(const QModelIndex& pIndex, int pRole) const
{
	if (pIndex.isValid() && pIndex.row() < rowCount())
	{
		auto pair = mSelfData.at(pIndex.row());
		if (pRole == Qt::DisplayRole || pRole == NAME)
		{
			return pair.first;
		}
		if (pRole == VALUE)
		{
			return pair.second;
		}
	}
	return QVariant();
}


QHash<int, QByteArray> SelfAuthModel::roleNames() const
{
	QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
	roles.insert(NAME, "name");
	roles.insert(VALUE, "value");
	return roles;
}


bool SelfAuthModel::event(QEvent* pEvent)
{
	if (pEvent->type() == QEvent::LanguageChange)
	{
		onSelfAuthenticationDataChanged();
	}
	return QAbstractListModel::event(pEvent);
}
