/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2025, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
#include "UnitTestPCH.h"
#include <assimp/SceneCombiner.h>
#include <assimp/mesh.h>
#include <memory>

using namespace ::Assimp;

class utSceneCombiner : public ::testing::Test {
    // empty
};

TEST_F(utSceneCombiner, MergeMeshes_ValidNames_Test) {
    MeshArray merge_list;
    aiMesh *mesh1 = new aiMesh;
    mesh1->mName.Set("mesh_1");
    merge_list.push_back(mesh1);

    aiMesh *mesh2 = new aiMesh;
    mesh2->mName.Set("mesh_2");
    merge_list.push_back(mesh2);

    aiMesh *mesh3 = new aiMesh;
    mesh3->mName.Set("mesh_3");
    merge_list.push_back(mesh3);

    std::unique_ptr<aiMesh> out;
    aiMesh *ptr = nullptr;
    SceneCombiner::MergeMeshes(&ptr, 0, merge_list.begin(), merge_list.end());
    out.reset(ptr);
    std::string outName = out->mName.C_Str();
    EXPECT_EQ("mesh_1.mesh_2.mesh_3", outName);
}

TEST_F(utSceneCombiner, CopySceneWithNullptr_AI_NO_EXCEPTion) {
    EXPECT_NO_THROW(SceneCombiner::CopyScene(nullptr, nullptr));
    EXPECT_NO_THROW(SceneCombiner::CopySceneFlat(nullptr, nullptr));
}
