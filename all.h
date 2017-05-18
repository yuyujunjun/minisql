#pragma once
#include"minisql.h"
#include"Interpreter.h"
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
#include"BufferManager.h"
#include"Btree_node.h"
#include"Bplus.h"
#include"Catalog.h"

#include"index.h"
#include"Interpreter.h"
const string RECORD("_record");
const string INDEX("_record_index");
const string CATA_REC("_catalog");
const string CATA_IND("_catalog_index");
