#ifndef CAFFE_UTIL_UPGRADE_PROTO_H_
#define CAFFE_UTIL_UPGRADE_PROTO_H_

#include <string>

#include "caffe/proto/caffe_pb.h"
#include "caffe/export.hpp"
namespace caffe {

// Return true iff the net is not the current version.
CAFFE_EXPORT bool NetNeedsUpgrade(const NetParameter& net_param);

// Check for deprecations and upgrade the NetParameter as needed.
CAFFE_EXPORT bool UpgradeNetAsNeeded(const string& param_file, NetParameter* param);

// Read parameters from a file into a NetParameter proto message.
CAFFE_EXPORT void ReadNetParamsFromTextFileOrDie(const string& param_file,
                                    NetParameter* param);
CAFFE_EXPORT void ReadNetParamsFromBinaryFileOrDie(const string& param_file,
                                      NetParameter* param);

// Return true iff any layer contains parameters specified using
// deprecated V0LayerParameter.
CAFFE_EXPORT bool NetNeedsV0ToV1Upgrade(const NetParameter& net_param);

// Perform all necessary transformations to upgrade a V0NetParameter into a
// NetParameter (including upgrading padding layers and LayerParameters).
CAFFE_EXPORT bool UpgradeV0Net(const NetParameter& v0_net_param, NetParameter* net_param);

// Upgrade NetParameter with padding layers to pad-aware conv layers.
// For any padding layer, remove it and put its pad parameter in any layers
// taking its top blob as input.
// Error if any of these above layers are not-conv layers.
CAFFE_EXPORT void UpgradeV0PaddingLayers(const NetParameter& param,
                            NetParameter* param_upgraded_pad);

// Upgrade a single V0LayerConnection to the V1LayerParameter format.
CAFFE_EXPORT bool UpgradeV0LayerParameter(const V1LayerParameter& v0_layer_connection,
                             V1LayerParameter* layer_param);

CAFFE_EXPORT V1LayerParameter_LayerType UpgradeV0LayerType(const string& type);

// Return true iff any layer contains deprecated data transformation parameters.
CAFFE_EXPORT bool NetNeedsDataUpgrade(const NetParameter& net_param);

// Perform all necessary transformations to upgrade old transformation fields
// into a TransformationParameter.
CAFFE_EXPORT void UpgradeNetDataTransformation(NetParameter* net_param);

// Return true iff the Net contains any layers specified as V1LayerParameters.
CAFFE_EXPORT bool NetNeedsV1ToV2Upgrade(const NetParameter& net_param);

// Perform all necessary transformations to upgrade a NetParameter with
// deprecated V1LayerParameters.
CAFFE_EXPORT bool UpgradeV1Net(const NetParameter& v1_net_param, NetParameter* net_param);

CAFFE_EXPORT bool UpgradeV1LayerParameter(const V1LayerParameter& v1_layer_param,
                             LayerParameter* layer_param);

CAFFE_EXPORT const char* UpgradeV1LayerType(const V1LayerParameter_LayerType type);

// Return true iff the Net contains input fields.
CAFFE_EXPORT bool NetNeedsInputUpgrade(const NetParameter& net_param);

// Perform all necessary transformations to upgrade input fields into layers.
CAFFE_EXPORT void UpgradeNetInput(NetParameter* net_param);

// Return true iff the solver contains any old solver_type specified as enums
CAFFE_EXPORT bool SolverNeedsTypeUpgrade(const SolverParameter& solver_param);

CAFFE_EXPORT bool UpgradeSolverType(SolverParameter* solver_param);

// Check for deprecations and upgrade the SolverParameter as needed.
CAFFE_EXPORT bool UpgradeSolverAsNeeded(const string& param_file, SolverParameter* param);

// Read parameters from a file into a SolverParameter proto message.
CAFFE_EXPORT void ReadSolverParamsFromTextFileOrDie(const string& param_file,
                                       SolverParameter* param);

}  // namespace caffe

#endif   // CAFFE_UTIL_UPGRADE_PROTO_H_
