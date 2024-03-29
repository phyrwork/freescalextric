classdef ProximityImageView < ChartView
    %LinescanView
    
    methods
        % constructor
        function obj = ProximityImageView(session, attribute, varargin)
            
            % initialise view
            obj = obj@ChartView(...
                session,varargin{:}, ...
                'xlabel', 'Image Index (px)', ...
                'ylabel', 'Intensity (16-bit raw)', ...
                'ytopc', 4096, ...
                'ybotc', 0, ...
                'xtopc', 128, ...
                'xbotc', 0 ...
                );
            
            % add series
            obj = obj.addSeries(@LinescanImageSeries, attribute);
            obj = obj.addSeries(@ProximityEdgesSeries, attribute);
        end
    end
end