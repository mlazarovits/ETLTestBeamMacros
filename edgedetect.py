import cv2
import numpy as np
import matplotlib.pyplot as plt
import ROOT


# tree = ROOT.TTree()
hist = ROOT.TH2F()  #('effmap','Prerad Efficiency Map')
file = ROOT.TFile('~/ETLTestBeamMacros/output/HPK3p1_4x4_prerad/HPK3p1_4x4_prerad.root')
file.GetObject('h_map_eff_0',hist)

xbins= hist.GetNbinsX()
ybins = hist.GetNbinsY()

imgMat = np.zeros((xbins,ybins))


for x in range(xbins):
	for y in range(ybins):
		imgMat[x][y] = 255*hist.GetBinContent(x,y)

#cast ints as uint8s
imgMat = np.uint8(imgMat)
imgMatT = np.transpose(imgMat)


#blur matrix image
# img_gausblur = cv2.GaussianBlur(imgMatT,(3,3),sigmaX=0.41)
# img_bilat= cv2.bilateralFilter(imgMatT,d=2,sigmaColor=180,sigmaSpace=180)
# img_2dfilter = cv2.filter2D(imgMatT,ddepth=-1,kernel=(5,5))


#get edges with Canny algorithm
edges = cv2.Canny(imgMat,650,1050)
edgesT = np.transpose(edges)

# edges_blur = cv2.GaussianBlur(edges,(3,3),sigmaX=0.41)
# edges_blur = cv2.bilateralFilter(edges,2,sigmaColor=0.5,sigmaSpace=0.9)
# edges = cv2.filter2D(edges,ddepth=-1,kernel=(2,2))
# edges = cv2.sepFilter2D(edges,-1,kernelX=1,kernelY=(3,3))

#find corners
dst = cv2.cornerHarris(edges,2,3,0.2)
dst = cv2.dilate(dst,None)
ret, dst = cv2.threshold(dst,0.01*dst.max(),255,0)
dstT = np.transpose(dst)
dst = np.uint8(dst)
#find corner centroids
ret, labels, stats, centroids = cv2.connectedComponentsWithStats(dst)
#define criteria to stop and define the corners
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.001)
corners = cv2.cornerSubPix(edges,np.float32(centroids),(11,11),(-1,-1),criteria)


# print(imgMat.shape)
# print(edges.shape)
# print(dst.shape)

maxX = hist.GetXaxis().GetXmax()
minX = hist.GetXaxis().GetXmin()
maxY = hist.GetYaxis().GetXmax()
minY = hist.GetYaxis().GetXmin()

nCorners = 16.*4.


# print(centroids[0])


hist_edges = ROOT.TH2F("hist_edges","hist_edges",xbins,minX,maxX,ybins,minY,maxY)
hist_corners = ROOT.TH2F("hist_corners","hist_corners",xbins,minX,maxX,ybins,minY,maxY)


pads = []

for x in range(xbins):
	for y in range(ybins):
		hist_edges.SetBinContent(x,y,edges[x][y])
		hist_corners.SetBinContent(x,y,dst[x][y])

		if edges[x][y] == dst[x][y]:
			cornerX = hist_edges.GetXaxis().GetBinCenter(x)
			cornerY = hist_edges.GetYaxis().GetBinCenter(y)
			pads.append((cornerX,cornerY))

		# if edges[x][y] == 255.0 and edges[x+1][y] == 255.0 and edges[x][y+1] == 255.0: #bottom left corner
		# 	hist_corners.SetBinContent(x,y,dst[x][y])
		# if edges[x][y] == 255.0 and edges[x-1][y] == 255.0 and edges[x][y+1] == 255.0: #bottom right corner
		# 	hist_corners.SetBinContent(x,y,dst[x][y])
		# if edges[x][y] == 255.0 and edges[x+1][y] == 255.0 and edges[x][y-1] == 255.0: #top left corner
		# 	hist_corners.SetBinContent(x,y,dst[x][y])
		# if edges[x][y] == 255.0 and edges[x-1][y] == 255.0 and edges[x][y-1] == 255.0: #top right corner
		# 	hist_corners.SetBinContent(x,y,0)
		
		# hist_corners.SetBinContent(x,y,dst[x][y])


# print(pads)

# for i
		# if dst[x][y] == 255.0:
		# 	# if x > edges.max
		# 	print("corner found!!")
		# 	print("x:",hist_corners.GetXaxis().GetBinCenter(x))
		# 	print("y:",hist_corners.GetYaxis().GetBinCenter(y))
	


		# corners = []
		# if edges[x][y] == 255.0 and edges[x+1][y] == 255.0 and edges[x][y+1] == 255.0: #bottom left corner
		# 	cornerX = hist_edges.GetXaxis().GetBinCenter(x)
		# 	cornerY = hist_edges.GetYaxis().GetBinCenter(y)

		# 	corners_bl.append((cornerX,cornerY))
		# 	# print((cornerX,cornerY))
		# if edges[x][y] == 255.0 and edges[x-1][y] == 255.0 and edges[x][y+1] == 255.0: #bottom right corner
		# 	cornerX = hist_edges.GetXaxis().GetBinCenter(x)
		# 	cornerY = hist_edges.GetYaxis().GetBinCenter(y)
		# 	corners_br.append((cornerX,cornerY))
		# if edges[x][y] == 255.0 and edges[x+1][y] == 255.0 and edges[x][y-1] == 255.0: #top left corner
		# 	cornerX = hist_edges.GetXaxis().GetBinCenter(x)
		# 	cornerY = hist_edges.GetYaxis().GetBinCenter(y)
		# 	corners_tl.append((cornerX,cornerY))
		# if edges[x][y] == 255.0 and edges[x-1][y] == 255.0 and edges[x][y-1] == 255.0: #top right corner
		# 	cornerX = hist_edges.GetXaxis().GetBinCenter(x)
		# 	cornerY = hist_edges.GetYaxis().GetBinCenter(y)
		# 	corners_tr.append((cornerX,cornerY))
		# # pads.append(corners)
		# if corners:
		# 	pads.append(corners)

# pads.sort()
# print(len(corners_br))
# print(len(corners_bl))
# print(len(corners_tr))
# print(len(corners_tl))

# print(corners_br)
# print(pads[0][1])
# corners = list(zip(corners_br,corners_bl,corners_tr,corners_tl))
# # corners = list(corners)
# print(corners[0])



# edgesmaxX = max(edges[:][0]) 
# edgesmaxY = max(edges[0])
# print(edgesmaxY,edgesmaxY)



c = ROOT.TCanvas()
c.cd()
# hist.SetOption("colz")

# hist.SetTitle("efficiency canny edges")
# cutstring = "x > "+str(pads[0][0][0])+ " && x < "+str(pads[0][0][1])
# print(cutstring)
hist.Draw("colz")
hist_edges.Draw("same")
# hist_corners.Draw("same")
# c.SetTitle("pad outlines")



c.SaveAs("hist_edges.pdf")
c.Close()

# plt.imshow(corners)
#####GRAYSCALE AND DEFAULT CANNY OUTPUT#####
# fig, ax = plt.subplots(3,1,figsize=(5,6.5))
# # plt.subplots_adjust(left = 0.12,  # the left side of the subplots of the figure
# # right = 0.9,   # the right side of the subplots of the figure
# # bottom = 0.01,  # the bottom of the subplots of the figure
# # top = 0.99,     # the top of the subplots of the figure
# # wspace = 0.01,  # the amount of width reserved for space between subplots,
# #          	  # expressed as a fraction of the average axis width
# # hspace = 0.05)
# # ax[0].subplot(211)
# ax[0].imshow(imgMatT,origin={'lower','lower'},cmap='plasma')
# ax[0].set_title('Original Image')
# # plt.xticks([]), plt.yticks([])
# # plt.subplot(212)
# ax[1].imshow(edges_gs,cmap='gray',origin={'lower','lower'})
# ax[1].set_title('Canny Edges')
# # plt.xticks([]), plt.yticks([])
# fig.savefig("og_gs_and_edges.pdf")



#####COLOR VS GRAYSCALE OG IMAGE#####
# b,g,r = cv2.split(img_color)
# img2 = cv2.merge([r,g,b])

# plt.subplot(221)
# plt.imshow(img2)
# plt.title('Original Image Color')
# plt.xticks([]), plt.yticks([])

# plt.subplot(222)
# plt.imshow(img_gs,cmap='gray')
# plt.title('Original Image Grayscale')
# plt.xticks([]), plt.yticks([])





####EDGES WITH DIFFERENT BLURRING#####
# plt.subplot(221)
# plt.imshow(edges_gs,cmap='gray')
# plt.title('Edge Image Grayscale')
# plt.xticks([]), plt.yticks([])

# plt.subplot(222)
# plt.imshow(edges_gs_box,cmap='gray')
# plt.title('Edge Image Grayscale, box blur')
# plt.xticks([]), plt.yticks([])

# plt.subplot(223)
# plt.imshow(edges_gs_med,cmap='gray')
# plt.title('Edge Image Grayscale, median blur')
# plt.xticks([]), plt.yticks([])

# plt.subplot(224)
# plt.imshow(edges_gs_med_box,cmap='gray')
# plt.title('Edge Image Grayscale, box + median blur')
# plt.xticks([]), plt.yticks([])





plt.show()

