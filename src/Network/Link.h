#ifndef CBLOCKS_LINK
#define CBLOCKS_LINK

namespace CBlocks{
  class Link{
  public:
    virtual bool connect();
    virtual bool isConnected();
    virtual void disconnect();
  };
}

#endif
