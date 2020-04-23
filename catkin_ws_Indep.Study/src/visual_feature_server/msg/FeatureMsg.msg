uint8 CORNER=1
uint8 BLOB=2
uint8 EDGE=3
string CORNER_STR="corner"
string BLOB_STR="blob"
string EDGE_STR="edge"

string name
int32 type

float32 image_scale
float32 world_scale

BlobFeatureMsg blobFeature
CornerFeatureMsg cornerFeature
EdgeFeatureMsg edgeFeature

#recognition confidence
float32 confidence
int32 x_pixel
int32 y_pixel
