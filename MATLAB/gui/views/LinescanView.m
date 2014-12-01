classdef LinescanView < LineChartView
    %LinescanView
    
    properties
        % attribute = char.empty; % attribute id
        % session   = []; % handle of session view is attached to
        % record    = []; % handle of record view is attached to
        % hfig      = []; % handle of figure (layout) view belongs to
        % haxis     = []; % handle of axis
        % atitle    = char.empty; % axis title
        % axlabel   = char.empty; % x-axis label
        % aylabel   = char.empty; % y-axis label
        % hplot     = []; % plot handle
        % period    = single.empty; % chart period (s) [REDUNDANT] 
    end
    
    methods
        % LinescanView constructor
        function obj = LinescanView(session, attribute, varargin)
            % parse input
            p = inputParser;
            addRequired (p, 'session');
            addRequired (p, 'attribute', @ischar);
            addParameter(p, 'figure', double.empty);
            addParameter(p, 'position', double.empty, @isnumeric);
            % addParameter(p, 'title', char.empty, @ischar);
            % addParameter(p, 'xlabel', char.empty, @ischar);
            % addParameter(p, 'ylabel', char.empty, @ischar);
            parse(p, session, attribute, varargin{:});
            
            % initialise LineChartView
            obj = obj@LineChartView(...
                p.Results.session,...
                p.Results.attribute,...
                'figure', p.Results.figure,...
                'position', p.Results.position,... 
                'title', ['Linescan Camera Image: ', strrep(attribute, '_', '\_')],...
                'xlabel', 'Position (px)',...
                'ylabel', 'Intensity (%/100)'...
            );
        end
        
        % draw chart - overload draw@LineChartView
        function obj = draw(obj)
            % set up data
            [x,y] = obj.record.peek();
            if (~isempty(y))
                x = 1:128;
            end
            
            % draw
            if (isempty(obj.hplot)) % initialise plot
                obj.hplot = plot(obj.haxis, x, y);
                obj = label(obj);
            else % replace plot data
                set(obj.hplot, 'XData', x, 'YData', y);
            end
        end
    end
    
end
