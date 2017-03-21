/*
 *Data-Pipeline
 *Copyright © 2017 Adrien Jeser <adrien@jeser.me>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU Affero General Public License as
 *published by the Free Software Foundation, either version 3 of the
 *License, or (at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU Affero General Public License for more details.
 *
 *You should have received a copy of the GNU Affero General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "store.h"

DpStore* __attribute__((overloadable)) DpStoreNew(DpType type, void* data) {
    DpStore* store = NULL;
    DpStoreCreate(&store, type, data);
    return store;
}

DpStore* __attribute__((overloadable)) DpStoreNew(int* data) {
    DpStore* store = NULL;
    DpStoreCreate(&store, kInteger, data);
    return store;
}

DpStore* __attribute__((overloadable)) DpStoreNew(char* data) {
    DpStore* store = NULL;
    DpStoreCreate(&store, kString, data);
    return store;
}

void DpStoreCreate(DpStore** store, DpType type, void* data) {
    *store = g_new(DpStore, 1);
    DpStoreInit(*store, type, data);
}

void DpStoreDestroy(DpStore** store) {
    DpStoreFree(*store);
    g_free(*store);
    *store = NULL;
}

void DpStoreInit(DpStore* self, DpType type, void* data) {
    self->type = type;
    self->data = data;
}

void DpStoreFree(DpStore* self) { (void)self; }

gboolean __attribute__((overloadable)) DpStoreSame(DpStore* self, DpType type) {
    return (self->type == type);
}
