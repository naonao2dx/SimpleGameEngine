//
//  SGPmdData.hpp
//  SimpleGameEngine
//
//  Created by 竹内 直 on 2018/06/15.
//  Copyright © 2018年 Nao. All rights reserved.
//

#ifndef SGPmdData_hpp
#define SGPmdData_hpp

#include <memory>
#include <vector>
#include "SGVertex.h"
#include "SGRawData.hpp"
#include <unordered_map>
#include "SGTexture2D.hpp"
#include "SGNode3D.hpp"

namespace SimpleGameEngine {
    struct PmdVertex {
        Vec3 position;
        Vec2 uv;
        Vec3 normal;
        struct Extra {
            GLshort boneNum[2];
            GLbyte boneWeight;
            GLbyte edgeFlag;
        } extra;
    };
    
    struct PmdMaterial {
        Vec4 diffuse;
        GLint indicesNum;
        GLchar diffuseTextureName[20 + 12];
        struct Extra {
            GLbyte edgeFlag;
            GLfloat shininess;
            Vec3 specularColor;
            Vec3 ambientColor;
            GLbyte toonIndex;
            GLchar effectTextureName[20 + 12];
        } extra;
    };
    
    struct PmdBone {
        GLchar name[20 + 12];
        /**
         * 親ボーン番号
         * 無い場合は0xFFFF = -1
         */
        GLshort parentBoneIndex;
        
        /**
         * ボーンの位置
         */
        Vec3 position;
        
        /**
         * サンプルでは使用しないが、PMDファイル仕様的に含まれている情報
         */
        struct {
            /**
             * 制御ボーン
             */
            GLshort tailPosBoneIndex;
            
            /**
             * ボーンの種類
             */
            GLbyte type;
            
            /**
             * IKボーン
             * サンプルではベイク済みもしくは手動制御を前提とする
             */
            GLshort ikParentBoneIndex;
        } extra;
    };

    
    struct PmdHeader
    {
        PmdHeader();
        GLfloat version;
        GLchar name[32];
        GLchar comment[256 + 128];
    };

    class PmdData : public Node3D
    {
    public:
        static std::shared_ptr<PmdData> create(std::string& filename);

        PmdData();
        virtual void draw() override;
        void loadHeader(RawData* data, PmdHeader* header);
        void loadVertices(RawData* data);
        void loadIndices(RawData* data);
        void loadMaterial(RawData* data);
        void loadBone(RawData* data);
        void createTextureList();
        void calcAABB();
        int32_t readLE32(RawData* data);
        int16_t readLE16(RawData* data);
        void readBytes(RawData* data, void* result, int bytes);
        PmdVertex* _vertices;
        GLuint _verticesNum;
        GLushort* _indices;
        GLuint _indicesNum;
        PmdMaterial* _materials;
        GLuint _materialsNum;
        PmdBone* _bones;
        GLuint _bonesNum;
        PmdHeader _header;
        Vec3 _minPoint;
        Vec3 _maxPoint;
        std::unordered_map<std::string, std::shared_ptr<Texture2D>> _textureList;
        std::shared_ptr<ShaderBase> shaderEdge;
    };
    
    
}

#endif /* SGPmdData_hpp */
