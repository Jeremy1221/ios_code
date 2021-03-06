//
//  AlbumListViewmodel.h
//  PhotoPick
//
//  Created by Jeremy on 2019/3/21.
//  Copyright © 2019 Jeremy. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Photos/Photos.h>

@class AlbumModel, PhotoModel;

typedef NS_ENUM(NSUInteger, AlbumListSelectionType) {
    AlbumListSelectionTypePhoto,
    AlbumListSelectionTypeVideo,
    AlbumListSelectionTypeAll,
};

typedef NS_ENUM(NSUInteger, AlbumListScrollDirection) {
    AlbumListScrollDirectionUp,         //上滑 也就是最新的在上面
    AlbumListScrollDirectionDown,       //下滑 最新的在底部
};

NS_ASSUME_NONNULL_BEGIN

@interface AlbumListViewmodel : NSObject
//////////////
//  选择前配置的选项
//////////////
/**
 每行多少个
 */
@property (nonatomic, assign) NSInteger columnCount;

/**
 时间排序， 默认 = yes
 */
@property (nonatomic, assign) BOOL reverseDate;

/**
 默认 all
 */
@property (nonatomic, assign) AlbumListSelectionType selectionType;
/**
 顶部还是底部 默认顶部 AlbumListScrollDirectionUp
 */
@property (nonatomic, assign) AlbumListScrollDirection scrollDirection;

///**
// null 意义不明 不允使用
// */
//@property (nonatomic, copy) NSArray<UIImage *> * localImages NS_DEPRECATED_IOS(2.0, 12.0);

/**
 是否单选 默认NO
 */
@property (nonatomic, assign) BOOL singleSelected;

/**
 单选是是否需要裁剪
 */
@property (nonatomic, assign) BOOL singleSelectedClip;

/**
 是否可以使用3DTouch预览  暂不支持 稍后开发
 */
@property (nonatomic, assign) BOOL open3DTouchPreview NS_DEPRECATED_IOS(2.0, 12.0);

/**
 在列表中展示GIF 默认 yes
 */
@property (nonatomic, assign) BOOL showGif;

/**
 在列表中展示Live图 默认 yes
 */
@property (nonatomic, assign) BOOL showLive;

/**
 最大选择数量 默认9
 */
@property (nonatomic, assign) NSInteger maxNum;

/**
 最大图片选择数量 默认9
 */
@property (nonatomic, assign) NSInteger maxPhotoNum;

/**
 最大视频选择数量 默认1
 */
@property (nonatomic, assign) NSInteger maxVideoNum;

/**
 最长视频时间 默认 max_float
 */
@property (nonatomic, assign) NSInteger maxVideoDuration;

/**
 最短视频时间 默认 0 无限制
 */
@property (nonatomic, assign) NSInteger minVideoDuration;

/**
 最大图片大小 (size)默认 CGSizeZero = CGSizeMax
 */
@property (nonatomic, assign) CGSize maxPhotoSize;

/**
 最小图片大小 (size)默认 CGSizeZero
 */
@property (nonatomic, assign) CGSize minPhotoSize;
/**
 是否在获取结果中使用压缩 默认 NO
 */
@property (nonatomic, assign) BOOL shouldCompress;

/**
 压缩质量 0-1 默认 1
 */
@property (nonatomic, assign) NSInteger quality;

/**
 压缩后图片类型 quality < 1时 肯定是jpeg = 1时 没啥卵用 默认 NO
 */
@property (nonatomic, assign) BOOL compressPNG NS_DEPRECATED_IOS(2.0, 12.0);

/**
 是否可以打开相机 默认 NO
 */
@property (nonatomic, assign) BOOL showCamera;

/**
 直接打开相机 貌似也没乱用 默认 NO
 */
@property (nonatomic, assign) BOOL openCameraDirect NS_DEPRECATED_IOS(2.0, 12.0);

/**
 是否保存照片到相机 默认 YES
 */
@property (nonatomic, assign) BOOL saveCameraPhotoToAlbum;

/**
 底部添加按钮 默认 NO
 */
@property (nonatomic, assign) BOOL showBottomView NS_DEPRECATED_IOS(2.0, 12.0);

/**
 collectionViewCell 要用到的icon
 */
@property (nonatomic, strong) NSDictionary<NSString *, UIImage *> *albumListCellIcon;

/**  系统相册发生了变化  */
@property (nonatomic, copy) void (^photoLibraryDidChangeWithPhotoViewController)(NSArray *collectionChanges);
@property (nonatomic, copy) void (^photoLibraryDidChangeWithPhotoPreviewViewController)(NSArray *collectionChanges);
@property (nonatomic, copy) void (^photoLibraryDidChangeWithVideoViewController)(NSArray *collectionChanges);
@property (nonatomic, copy) void (^photoLibraryDidChangeWithPhotoView)(NSArray *collectionChanges ,BOOL selectPhoto);

//////////////
//  完成选择之后获取的内容
//////////////

/**
 意义不明 猜测是将要存储的相册 相机胶卷 || 所有照片
 */
@property (nonatomic, strong) AlbumModel * albumModel;

/**
 选择后的数组
 */
@property (nonatomic, strong) NSMutableArray * selectedList;

/**
 选择后的照片数组
 */
@property (nonatomic, strong) NSMutableArray * _Nullable selectedPhotos;

/**
 选择后的视频数组
 */
@property (nonatomic, strong) NSMutableArray * _Nullable selectedVideos;

/**
 裁剪后的照片
 */
@property (nonatomic, strong) UIImage * _Nullable selectedImage;
/**
 裁剪前的原照
 */
@property (nonatomic, strong) UIImage * _Nullable selectedOriginImage;
/**
 裁剪后的照片的上传的路径
 */
@property (nonatomic, copy) NSString * _Nullable uploadPath;
/**
 裁剪后的原照的上传的路径
 */
@property (nonatomic, copy) NSString * _Nullable uploadOriginPath;

/**
 所有相册
 */
@property (strong, nonatomic, readonly) NSArray<AlbumModel *> *albums;

/**
 是否正在选择照片
 */
@property (assign, nonatomic) BOOL selecting;

/**
 初始化方法

 @param selectionType <#selectionType description#>
 @return <#return value description#>
 */
- (instancetype)initWithSelectionType:(AlbumListSelectionType)selectionType;

/**
 获取全部相册 (只是相册 不包含图片)

 @param albums <#albums description#>
 */
- (void)fetchAllAlbum:(void(^)(NSArray<AlbumModel *> *albums))albums;

/**
 获取所有相册 (只是相册 不包含图片)

 @param firstAlbum 拿到第一个相册后回调一次
 @param albums 所有相册的回调
 @param onlyFirst 是否只需获取 相机胶卷或所有照片
 */
- (void)getAllAlbum:(void(^)(AlbumModel *firstAlbum))firstAlbum
             albums:(void(^)(NSArray<AlbumModel *> *albums))albums
          onlyFirst:(BOOL)onlyFirst;

/**
 获取相册中的照片

 @param result <#result description#>
 @param index <#index description#>
 @param list <#list description#>
 */
- (void)fetchPhotoForPHResult:(PHFetchResult *)result
                        index:(NSInteger)index
                       result:(void(^)(NSArray<PhotoModel *> * photos, NSArray<PhotoModel *> * videos, NSArray<PhotoModel *> * objs))list;

- (void)getAllPhotoForAlbum:(AlbumModel *)albumModel
                   complete:(void (^)(NSArray<PhotoModel *> *allList, NSArray<PhotoModel *> *previewList, NSArray<PhotoModel *> *photoList, NSArray<PhotoModel *> *videoList, PhotoModel *firstSelectModel))complete;

/**
 删除选中的照片
 @param index <#index description#>
 */
- (void)removeSelectdAtIndex:(NSInteger)index;

/**
 删除所有选中的照片
 */
- (void)clearSelectedList;

/**
 生成Cell用于展示照片属性的Icon Image
 */
- (void)getCellIcons;

@end

NS_ASSUME_NONNULL_END
