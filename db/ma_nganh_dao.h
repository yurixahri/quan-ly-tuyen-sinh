#ifndef MA_NGANH_DAO_H
#define MA_NGANH_DAO_H

#include "db/models/ma_nganh.h"
#include "db/models/ma_nganh_tohop.h"
#include "db/models/nganh.h"
#include "db/models/to_hop_mon.h"
#include "db/models/ptxt.h"

inline bool addMaNganh(long &id_nganh, QList<QVariant> &list_tohop, int &chi_tieu, QString &ghi_chu){
    ma_nganh_ptr adding;
    adding.reset(new ma_nganh());
    adding->nganh = std::make_shared<nganh>(id_nganh);
    adding->chi_tieu = chi_tieu;
    adding->ghi_chu = ghi_chu;

    for (auto &item : list_tohop){
        auto temp = std::make_shared<ma_nganh_tohop>();
        temp->id_nganh = id_nganh;
        temp->tohop = std::make_shared<tohop_mon>(item.toLongLong());
        adding->list_tohop.append(temp);
    }

    qx::QxSession session;
    session += qx::dao::insert(adding, session.database());
    //session += qx::dao::insert(adding->list_tohop, session.database());

    for (auto &item : adding->list_tohop){
        session += qx::dao::insert(item, session.database());
    }
    if (!session.isValid()){
        return false;
    }
    else
        return true;
}

inline bool changeMaNganh(ma_nganh_ptr &edit_item, QList<QVariant> &list_tohop, int &chi_tieu, QString &ghi_chu){
    qx::QxSession session;
    for (auto &item : edit_item->list_tohop) session += qx::dao::delete_by_id(item, session.database());
    edit_item->list_tohop.clear();
    edit_item->chi_tieu = chi_tieu;
    edit_item->ghi_chu = ghi_chu;

    for (auto &item : list_tohop){
        auto temp = std::make_shared<ma_nganh_tohop>();
        temp->id_nganh = edit_item->nganh->id;
        temp->tohop = std::make_shared<tohop_mon>(item.toLongLong());
        edit_item->list_tohop.append(temp);
    }

    for (auto &item : edit_item->list_tohop){
        session += qx::dao::insert(item, session.database());
    }
    session += qx::dao::update(edit_item, session.database());
    if (!session.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<ma_nganh_ptr>> getAllMaNganh(){
    QList<ma_nganh_ptr> list;

    qx::QxSession session;

    // relations << "id_nganh.id_nhom_nganh";

    session += qx::dao::fetch_all_with_relation("*->*", list, session.database());
    for (auto &item : list){
        qx_query query;
        query.where("id_nganh").isEqualTo(QVariant::fromValue(item->nganh->id));
        session += qx::dao::fetch_by_query_with_all_relation(query, item->list_tohop, session.database());
    }

    if (!session.isValid()) {
        qDebug() << session.allErrors();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<ma_nganh_ptr> getMaNganhById(long &id){
    ma_nganh_ptr item = std::make_shared<ma_nganh>(id);
    qx::QxSession session;
    session += qx::dao::fetch_by_id_with_relation("*->*", item);
    qx_query query;
    query.where("id_nganh").isEqualTo(QVariant::fromValue(item->nganh->id));
    session += qx::dao::fetch_by_query_with_all_relation(query, item->list_tohop, session.database());

    if (!session.isValid()) {
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteMaNganhById(long &id){
    qx::QxSession session;
    auto item = std::make_shared<ma_nganh>(id);
    session += qx::dao::delete_by_id<>(item, session.database());

    if (!session.isValid()) {
        return false;
    } else {
        return true;
    }
}

inline bool deleteAllMaNganh(){
    qx::QxSession session;
    session += qx::dao::delete_all<ma_nganh>(session.database());

    if (!session.isValid()) {
        return false;
    } else {
        return true;
    }
}

#endif // MA_NGANH_DAO_H
