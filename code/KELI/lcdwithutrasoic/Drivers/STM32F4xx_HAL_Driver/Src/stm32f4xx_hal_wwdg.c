stance_Proxy(
    ISpObjectToken* This,
    IUnknown *pUnkOuter,
    DWORD dwClsContext,
    REFIID riid,
    void **ppvObject);
void __RPC_STUB ISpObjectToken_CreateInstance_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISpObjectToken_GetStorageFileName_Proxy(
    ISpObjectToken* This,
    REFCLSID clsidCaller,
    LPCWSTR pszValueName,
    LPCWSTR pszFileNameSpecifier,
    ULONG nFolder,
    LPWSTR *ppszFilePath);
void __RPC_STUB ISpObjectToken_GetStorageFileName_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISpObjectToken_RemoveStorageFileName_Proxy(
    ISpObjectToken* This,
    REFCLSID clsidCaller,
    LPCWSTR pszKeyName,
    WINBOOL fDeleteFile);
void __RPC_STUB ISpObjectToken_RemoveStorageFileName_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISpObjectToken_Remove_Proxy(
    ISpObjectToken* This,
    const CLSID *pclsidCaller);
void __RPC_STUB ISpObjectToken_Remove_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);
HRESULT STDMETHODCALLTYPE ISpObjectToken_MatchesAttributes_Proxy(
    ISpObjectToken* This,
    LPCWSTR pszAttributes,
    WINBOOL *pfMatches);
void __RPC_STUB ISpObjectToken_MatchesAttributes_Stub(
    IRpcStubBuffer* This,
    IRpcChannelBuffer* pRpcChannelBuffer,
    PRPC_MESSAGE pRpcMessage,
    DWORD* pdwStubPhase);

#endif  /* __ISpObjectToken_INTERFACE_DEFINED__ */

/*****************************************************************************
 * ISpObjectTokenInit interface
 */
#ifndef __ISpObjectTokenInit_INTERFACE_DEFINED__
#define __ISpObjectTokenInit_INTERFACE_DEFINED__

DEFINE_GUID(IID_ISpObjectTokenInit, 0xb8aab0cf, 0x346f, 0x49d8, 0x94,0x99, 0xc8,0xb0,0x3f,0x16,0x1d,0x51);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("b8aab0cf-346f-49d8-9499-c8b03f161d51")
ISpObjectTokenInit : public ISpObjectToken
{
    virtual HRESULT STDMETHODCALLTYPE InitFromDataKey(
        LPCWSTR pszCategoryId,
        LPCWSTR pszTokenId,
        ISpDataKey *pDataKey) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ISpObjectTokenInit, 0xb8aab0cf, 0x346f, 0x49d8, 0x94,0x99, 0xc8,0xb0,0x3f,0x16,0x1d,0x51)
#endif
#else
typedef struct ISpObjectTokenInitVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ISpObjectTokenInit* This,
        REFIID riid,
        void **ppvObject);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ISpObjectTokenInit* This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ISpObjectTokenInit* This);

    /*** ISpDataKey methods ***/
    HRESULT (STDMETHODCALLTYPE *SetData)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        ULONG cbData,
        const BYTE *pData);

    HRESULT (STDMETHODCALLTYPE *GetData)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        ULONG *pcbData,
        BYTE *pData);

    HRESULT (STDMETHODCALLTYPE *SetStringValue)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        LPCWSTR pszValue);

    HRESULT (STDMETHODCALLTYPE *GetStringValue)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        LPWSTR *ppszValue);

    HRESULT (STDMETHODCALLTYPE *SetDWORD)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        DWORD dwValue);

    HRESULT (STDMETHODCALLTYPE *GetDWORD)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName,
        DWORD *pdwValue);

    HRESULT (STDMETHODCALLTYPE *OpenKey)(
        ISpObjectTokenInit* This,
        LPCWSTR pszSubKeyName,
        ISpDataKey **ppSubKey);

    HRESULT (STDMETHODCALLTYPE *CreateKey)(
        ISpObjectTokenInit* This,
        LPCWSTR pszSubKey,
        ISpDataKey **ppSubKey);

    HRESULT (STDMETHODCALLTYPE *DeleteKey)(
        ISpObjectTokenInit* This,
        LPCWSTR pszSubKey);

    HRESULT (STDMETHODCALLTYPE *DeleteValue)(
        ISpObjectTokenInit* This,
        LPCWSTR pszValueName);

    HRESULT (STDMETHODCALLTYPE *EnumKeys)(
        ISpObjectTokenInit* This,
        ULONG Index,
        LPWSTR *ppszSubKeyName);

    HRESULT (STDMETHODCALLTYPE *EnumValues)(
        ISpObjectTokenInit* This,
        ULONG Index,
        LPWSTR *ppszValueName);

    /*** ISpObjectToken methods ***/
    HRESULT (STDMETHODCALLTYPE *SetId)(
        ISpObjectTokenInit* This,
        LPCWSTR pszCategoryId,
        LPCWSTR pszTokenId,
        WINBOOL fCreateIfNotExist);

    HRESULT (STDMETHODCALLTYPE *GetId)(
        ISpObjectTokenInit* This,
        LPWSTR *ppszCoMemTokenId);

    HRESULT (STDMETHODCALLTYPE *GetCategory)(
        ISpObjectTokenInit* This,
        ISpObjectTokenCategory **ppTokenCategory);

    HRESULT (STDMETHODCALLTYPE *CreateInstance)(
        ISpObjectTokenInit* This,
        IUnknown *pUnkOuter,
        DWORD dwClsContext,
        REFIID riid,
        void **ppvObject);

    HRESULT (STDMETHODCALLTYPE *GetStorageFileName)(
        ISpObjectTokenInit* This,
        REFCLSID clsidCaller,
        LPCWSTR pszValueName,
        LPCWSTR pszFileNameSpecifier,
        ULONG nFolder,
        LPWSTR *ppszFilePath);

    HRESULT (STDMETHODCALLTYPE *RemoveStorageFileName)(
        ISpObjectTokenInit* This,
        REFCLSID clsidCaller,
        LPCWSTR pszKeyName,
        WINBOOL fDeleteFile);

    HRESULT (STDMETHODCALLTYPE *Remove)(
        ISpObjectTokenInit* This,
        const CLSID *pclsidCaller);

    HRESULT (STDMETHODCALLTYPE *IsUISupported)(
        ISpObjectTokenInit* This,
        LPCWSTR pszTypeOfUI,
        void *pvExtraData,
        ULONG cbExtraData,
        IUnknown *punkObject,
        WINBOOL *pfSupported);

    HRESULT (STDMETHODCALLTYPE *DisplayUI)(
        ISpObjectTokenInit* This,
        HWND hwndParent,
        LPCWSTR pszTitle,
        LPCWSTR pszTypeOfUI,
        void *pvExtraData,
        ULONG cbExtraData,
        IUnknown *punkObject);

    HRESULT (STDMETHODCALLTYPE *MatchesAttributes)(
        ISpObjectTokenInit* This,
        LPCWSTR pszAttributes,
        WINBOOL *pfMatches);

    /*** ISpObjectTokenInit methods ***/
    HRESULT (STDMETHODCALLTYPE *InitFromDataKey)(
        ISpObjectTokenInit* This,
        LPCWSTR pszCategoryId,
        LPCWSTR pszTokenId,
        ISpDataKey *pDataKey);

    END_INTERFACE
} ISpObjectTokenInitVtbl;
interface ISpObjectTokenInit {
    CONST_VTBL ISpObjectTokenInitVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ISpObjectTokenInit_QueryInterface(This,riid,ppvObject) (This)->lpVtbl->QueryInterface(This,riid,ppvObject)
#define ISpObjectTokenInit_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ISpObjectTokenInit_Release(This) (This)->lpVtbl->Release(This)
/*** ISpDataKey methods ***/
#define ISpObjectTokenInit_SetData(This,pszValueName,cbData,pData) (This)->lpVtbl->SetData(This,pszValueName,cbData,pData)
#define ISpObjectTokenInit_GetData(This,pszValueName,pcbData,pData) (This)->lpVtbl->GetData(This,pszValueName,pcbData,pData)
#define ISpObjectTokenInit_SetStringValue(This,pszValueName,pszValue) (This)->lpVtbl->SetStringValue(This,pszValueName,pszValue)
#define ISpObjectTokenInit_GetStringValue(This,pszValueName,ppszValue) (This)->lpVtbl->GetStringValue(This,pszValueName,ppszValue)
#define ISpObjectTokenInit_SetDWORD(This,pszValueName,dwValue) (This)->lpVtbl->SetDWORD(This,pszValueName,dwValue)
#define ISpObjectTokenInit_GetDWORD(This,pszValueName,pdwValue) (This)->lpVtbl->GetDWORD(This,pszValueName,pdwValue)
#define ISpObjectTokenInit_OpenKey(This,pszSubKeyName,ppSubKey) (This)->lpVtbl->OpenKey(This,pszSubKeyName,ppSubKey)
#define ISpObjectTokenInit_CreateKey(This,pszSubKey,ppSubKey) (This)->lpVtbl->CreateKey(This,pszSubKey,ppSubKey)
#define ISpObjectTokenInit_DeleteKey(This,pszSubKey) (This)->lpVtbl->DeleteKey(This,pszSubKey)
#define ISpObjectTokenInit_DeleteValue(This,pszValueName) (This)->lpVtbl->DeleteValue(This,pszValueName)
#define ISpObjectTokenInit_EnumKeys(This,Index,ppszSubKeyName) (This)->lpVtbl->EnumKeys(This,Index,ppszSubKeyName)
#define ISpObjectTokenInit_EnumValues(This,Index,ppszValueName) (This)->lpVtbl->EnumValues(This,Index,ppszValueName)
/*** ISpObjectToken methods ***/
#define ISpObjectTokenInit_SetId(This,pszCategoryId,pszTokenId,fCreateIfNotExist) (This)->lpVtbl->SetId(This,pszCategoryId,pszTokenId,fCreateIfNotExist)
#define ISpObjectTokenInit_GetId(This,ppszCoMemTokenId) (This)->lpVtbl->GetId(This,ppszCoMemTokenId)
#define ISpObjectTokenInit_GetCategory(This,ppTokenCategory) (This)->lpVtbl->GetCategory(This,ppTokenCategory)
#define ISpObjectTokenInit_CreateInstance(This,pUnkOuter,dwClsContext,riid,ppvObject) (This)->lpVtbl->CreateInstance(This,pUnkOuter,dwClsContext,riid,ppvObject)
#define ISpObjectTokenInit_GetStorageFileName(This,clsidCaller,pszValueName,pszFileNameSpecifier,nFolder,ppszFilePath) (This)->lpVtbl->GetStorageFileName(This,clsidCaller,pszValueName,pszFileNameSpecifier,nFolder,ppszFilePath)
#define ISpObjectTokenInit_RemoveStorageFileName(This,clsidCaller,pszKeyName,fDeleteFile) (This)->lpVtbl->RemoveStorageFileName(This,clsidCaller,pszKeyName,fDeleteFile)
#define ISpObjectTokenInit_Remove(This,pclsidCaller) (This)->lpVtbl->Remove(This,pclsidCaller)
#define ISpObjectTokenInit_IsUISupported(This,pszTypeOfUI,pvExtraData,cbExtraData,punkObject,pfSupported) (This)->lpVtbl->IsUISupported(This,pszTypeOfUI,pvExtraData,cbExtraData,punkObject,pfSupported)
#define ISpObjectTokenInit_DisplayUI(This,hwndParent,pszTitle,pszTypeOfUI,pvExtraData,cbExtraData,punkObject) (This)->lpVtbl->DisplayUI(This,hwndParent,pszTitle,pszTypeOfUI,pvExtraData,cbExtraData,punkObject)
#define ISpObjectTokenInit_MatchesAttributes(This,pszAttributes,pfMatches) (This)->lpVtbl->MatchesAttributes(This,pszAttributes,pfMatches)
/*** ISpObjectTokenInit methods ***/
#define ISpObjectTokenInit_InitFromDataKey(This,pszCategoryId,pszTokenId,pDataKey) (This)->lpVtbl->InitFromDataKey(This,pszCategoryId,pszTokenId,pDataKey)
#else
/*** IUnknown methods ***/
static FORCEINLINE HRESULT ISpObjectTokenInit_QueryInterface(ISpObjectTokenInit* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->QueryInterface(This,riid,ppvObject);
}
static FORCEINLINE ULONG ISpObjectTokenInit_AddRef(ISpObjectTokenInit* This) {
    return This->lpVtbl->AddRef(This);
}
static FORCEINLINE ULONG ISpObjectTokenInit_Release(ISpObjectTokenInit* This) {
    return This->lpVtbl->Release(This);
}
/*** ISpDataKey methods ***/
static FORCEINLINE HRESULT ISpObjectTokenInit_SetData(ISpObjectTokenInit* This,LPCWSTR pszValueName,ULONG cbData,const BYTE *pData) {
    return This->lpVtbl->SetData(This,pszValueName,cbData,pData);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetData(ISpObjectTokenInit* This,LPCWSTR pszValueName,ULONG *pcbData,BYTE *pData) {
    return This->lpVtbl->GetData(This,pszValueName,pcbData,pData);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_SetStringValue(ISpObjectTokenInit* This,LPCWSTR pszValueName,LPCWSTR pszValue) {
    return This->lpVtbl->SetStringValue(This,pszValueName,pszValue);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetStringValue(ISpObjectTokenInit* This,LPCWSTR pszValueName,LPWSTR *ppszValue) {
    return This->lpVtbl->GetStringValue(This,pszValueName,ppszValue);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_SetDWORD(ISpObjectTokenInit* This,LPCWSTR pszValueName,DWORD dwValue) {
    return This->lpVtbl->SetDWORD(This,pszValueName,dwValue);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetDWORD(ISpObjectTokenInit* This,LPCWSTR pszValueName,DWORD *pdwValue) {
    return This->lpVtbl->GetDWORD(This,pszValueName,pdwValue);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_OpenKey(ISpObjectTokenInit* This,LPCWSTR pszSubKeyName,ISpDataKey **ppSubKey) {
    return This->lpVtbl->OpenKey(This,pszSubKeyName,ppSubKey);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_CreateKey(ISpObjectTokenInit* This,LPCWSTR pszSubKey,ISpDataKey **ppSubKey) {
    return This->lpVtbl->CreateKey(This,pszSubKey,ppSubKey);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_DeleteKey(ISpObjectTokenInit* This,LPCWSTR pszSubKey) {
    return This->lpVtbl->DeleteKey(This,pszSubKey);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_DeleteValue(ISpObjectTokenInit* This,LPCWSTR pszValueName) {
    return This->lpVtbl->DeleteValue(This,pszValueName);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_EnumKeys(ISpObjectTokenInit* This,ULONG Index,LPWSTR *ppszSubKeyName) {
    return This->lpVtbl->EnumKeys(This,Index,ppszSubKeyName);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_EnumValues(ISpObjectTokenInit* This,ULONG Index,LPWSTR *ppszValueName) {
    return This->lpVtbl->EnumValues(This,Index,ppszValueName);
}
/*** ISpObjectToken methods ***/
static FORCEINLINE HRESULT ISpObjectTokenInit_SetId(ISpObjectTokenInit* This,LPCWSTR pszCategoryId,LPCWSTR pszTokenId,WINBOOL fCreateIfNotExist) {
    return This->lpVtbl->SetId(This,pszCategoryId,pszTokenId,fCreateIfNotExist);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetId(ISpObjectTokenInit* This,LPWSTR *ppszCoMemTokenId) {
    return This->lpVtbl->GetId(This,ppszCoMemTokenId);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetCategory(ISpObjectTokenInit* This,ISpObjectTokenCategory **ppTokenCategory) {
    return This->lpVtbl->GetCategory(This,ppTokenCategory);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_CreateInstance(ISpObjectTokenInit* This,IUnknown *pUnkOuter,DWORD dwClsContext,REFIID riid,void **ppvObject) {
    return This->lpVtbl->CreateInstance(This,pUnkOuter,dwClsContext,riid,ppvObject);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_GetStorageFileName(ISpObjectTokenInit* This,REFCLSID clsidCaller,LPCWSTR pszValueName,LPCWSTR pszFileNameSpecifier,ULONG nFolder,LPWSTR *ppszFilePath) {
    return This->lpVtbl->GetStorageFileName(This,clsidCaller,pszValueName,pszFileNameSpecifier,nFolder,ppszFilePath);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_RemoveStorageFileName(ISpObjectTokenInit* This,REFCLSID clsidCaller,LPCWSTR pszKeyName,WINBOOL fDeleteFile) {
    return This->lpVtbl->RemoveStorageFileName(This,clsidCaller,pszKeyName,fDeleteFile);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_Remove(ISpObjectTokenInit* This,const CLSID *pclsidCaller) {
    return This->lpVtbl->Remove(This,pclsidCaller);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_IsUISupported(ISpObjectTokenInit* This,LPCWSTR pszTypeOfUI,void *pvExtraData,ULONG cbExtraData,IUnknown *punkObject,WINBOOL *pfSupported) {
    return This->lpVtbl->IsUISupported(This,pszTypeOfUI,pvExtraData,cbExtraData,punkObject,pfSupported);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_DisplayUI(ISpObjectTokenInit* This,HWND hwndParent,LPCWSTR pszTitle,LPCWSTR pszTypeOfUI,void *pvExtraData,ULONG cbExtraData,IUnknown *punkObject) {
    return This->lpVtbl->DisplayUI(This,hwndParent,pszTitle,pszTypeOfUI,pvExtraData,cbExtraData,punkObject);
}
static FORCEINLINE HRESULT ISpObjectTokenInit_MatchesAttributes(ISpObjectTokenInit* This,LPCWSTR pszAttributes,WINBOOL *pfMatches) {
    return This->lpVtbl->MatchesAttributes(This,pszAttributes,pfMatches);
}
/*** ISpObjectTokenInit methods ***/
static FORCEINLINE HRESULT ISpObjectTokenInit_InitFromDataKey(ISpObjectTokenInit* This,LPCWSTR pszCategoryId,LPCWSTR pszTokenId,ISpDataKey *pDataKey) {
    return This->lpVtbl->InitFromDataKey(This,pszCategoryId,pszTokenId,pDataKey);
}
#endif
#endif

#endif

HRESULT STDMETHODCALLTYPE ISpObjectTokenInit_InitFromDataKey_Proxy(
    ISpObjectTokenInit* This,
    LPCWSTR pszCategor