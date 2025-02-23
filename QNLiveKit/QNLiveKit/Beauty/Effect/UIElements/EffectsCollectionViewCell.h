//
//  EffectsCollectionViewCell.h
//  SenseMeEffects
//
//  Created by Lin Sun on 2018/12/8.
//  Copyright © 2018 SenseTime. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SenseArSourceService.h"
#import "STParamUtil.h"
#import "EFSenseArMaterialDataModels.h"
typedef enum : NSUInteger {
    NotDownloaded = 0,
    IsDownloading,
    Downloaded,
    IsSelected
} ModelState;

@interface EffectsCollectionViewCellModel : NSObject
@property (nonatomic , assign) int packageId;
@property (nonatomic , assign) ModelState state;
@property (nonatomic , assign) int indexOfItem;
@property (nonatomic , assign) STEffectsType iEffetsType;
@property (nonatomic , strong) UIImage *imageThumb;
@property (nonatomic , copy) NSString *imageThumbUrl;
@property (nonatomic , strong) SenseArMaterial *material;
@property (nonatomic , strong) EFDataSourceModel *NewMaterial;
@property (nonatomic , copy) NSString *strMaterialPath;
@property (nonatomic , copy) NSString *NameOne;
@property (nonatomic , copy) NSString *NameTwo;
@property (nonatomic , copy) NSString *NameThree;

@end

@interface EffectsCollectionViewCell : UICollectionViewCell

@property (nonatomic , strong) EffectsCollectionViewCellModel *model;

@property (weak, nonatomic) IBOutlet UIImageView *thumbView;
@property (weak, nonatomic) IBOutlet UIImageView *loadingView;
@property (weak, nonatomic) IBOutlet UIImageView *downloadSign;


@end


